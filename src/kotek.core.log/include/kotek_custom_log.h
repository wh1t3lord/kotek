#pragma once

/// \file kotek_custom_log.h
/// \~english kotek's own no-dependency logging backend (task K17/K4
/// logging-CUSTOM): the narrow surface every logging macro in the engine
/// consumes — info/warn/error/trace of a pre-formatted c-string, exactly
/// matching the spdlog::logger method names so the macro bodies are
/// backend-identical. One instance is the "all" logger (file + console),
/// the other is the "tracer" (debug output window + console). No
/// third-party anything: an OS file handle, C stdio for the console, the
/// OS for the debug window. Users keep the K21/re-registration path to
/// replace this class with their own logging — this is kotek's built-in
/// floor, not a cage.
///
/// The file sink is a raw OS handle, NOT a CRT FILE*: one instance is
/// shared by every module through Set_LoggerMain bridging (constructed in
/// the exe, driven by game.ktk's header-inline code) and each module has
/// its own CRT under /MT — a FILE* from one CRT is invalid in another
/// (fwrite silently fails and the log file stays empty while console
/// output keeps working), an OS handle is valid process-wide. Writes are
/// serialized with a mutex: spdlog's _mt loggers were thread-safe, this
/// backend must be too (the history stress mix logs from worker threads).

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <mutex>

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
#endif

// the log file is BOUNDED: at this size it rotates to <name>.prev (single
// generation, overwritten) instead of growing without end — an append-only
// engine log reached 1.4 GB from repeated boots before this rule existed
#define KOTEK_DEF_CUSTOM_LOG_MAX_FILE_SIZE (64U * 1024U * 1024U)
#define KOTEK_DEF_CUSTOM_LOG_PATH_MAX 260

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkCustomLogger
{
public:
	/// \~english p_file_path may be nullptr (console-only logger); when the
	/// file fails to open the logger degrades to console-only instead of
	/// aborting the process — logging must never be a fatal subsystem
	explicit ktkCustomLogger(const char* p_file_path,
		bool to_debug_window) noexcept :
		m_to_debug_window{to_debug_window}
	{
		if (p_file_path)
		{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
			// FILE_APPEND_DATA gives O_APPEND semantics: every WriteFile
			// lands at the end of the file regardless of the file pointer
			this->m_file_handle = CreateFileA(p_file_path, FILE_APPEND_DATA,
				FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
				nullptr);

			if (this->m_file_handle == INVALID_HANDLE_VALUE)
			{
				this->m_file_handle = nullptr;
			}

			// the path is kept for rotation (the log is bounded — see
			// KOTEK_DEF_CUSTOM_LOG_MAX_FILE_SIZE); a pre-existing file's
			// size counts against the budget
			strncpy_s(this->m_file_path, p_file_path, _TRUNCATE);

			LARGE_INTEGER existing{};
			if (this->m_file_handle &&
			    GetFileSizeEx(this->m_file_handle, &existing))
			{
				this->m_bytes_written =
					static_cast<size_t>(existing.QuadPart);
			}
#else
			this->m_p_file = fopen(p_file_path, "a");
#endif
		}
	}

	~ktkCustomLogger(void)
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_file_handle)
		{
			CloseHandle(this->m_file_handle);
		}
#else
		if (this->m_p_file)
		{
			fclose(this->m_p_file);
		}
#endif
	}

	ktkCustomLogger(const ktkCustomLogger&) = delete;
	ktkCustomLogger& operator=(const ktkCustomLogger&) = delete;

	void info(const char* p_text) noexcept { this->Write("info", p_text); }
	void warn(const char* p_text) noexcept { this->Write("warning", p_text); }
	void error(const char* p_text) noexcept { this->Write("error", p_text); }
	void trace(const char* p_text) noexcept { this->Write("trace", p_text); }

	// the fmt-shaped call surface spdlog's macros use
	// (info("[{}:{}:{}] {}", file, func, line, text)): a minimal
	// sequential-{} substitution, NOT a general fmt — only the patterns
	// the engine's macros actually emit
	template <typename... Args>
	void info(const char* p_fmt, Args&&... args) noexcept
	{
		this->Write_Variadic("info", p_fmt, args...);
	}
	template <typename... Args>
	void warn(const char* p_fmt, Args&&... args) noexcept
	{
		this->Write_Variadic("warning", p_fmt, args...);
	}
	template <typename... Args>
	void error(const char* p_fmt, Args&&... args) noexcept
	{
		this->Write_Variadic("error", p_fmt, args...);
	}
	template <typename... Args>
	void trace(const char* p_fmt, Args&&... args) noexcept
	{
		this->Write_Variadic("trace", p_fmt, args...);
	}

	void flush(void) noexcept
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_file_handle)
		{
			FlushFileBuffers(this->m_file_handle);
		}
#else
		if (this->m_p_file)
		{
			fflush(this->m_p_file);
		}
#endif
	}

private:
	static void append_arg(char*& p_cursor, size_t& remaining,
		const char* p_value) noexcept
	{
		if (p_value == nullptr)
			p_value = "(null)";

		const int written = snprintf(p_cursor, remaining, "%s", p_value);

		if (written > 0)
		{
			p_cursor += written;
			remaining -= static_cast<size_t>(written);
		}
	}

	static void append_arg(char*& p_cursor, size_t& remaining,
		char* p_value) noexcept
	{
		append_arg(p_cursor, remaining, const_cast<const char*>(p_value));
	}

	static void append_arg(char*& p_cursor, size_t& remaining,
		int value) noexcept
	{
		const int written = snprintf(p_cursor, remaining, "%d", value);

		if (written > 0)
		{
			p_cursor += written;
			remaining -= static_cast<size_t>(written);
		}
	}

	static void append_arg(char*& p_cursor, size_t& remaining,
		unsigned int value) noexcept
	{
		const int written = snprintf(p_cursor, remaining, "%u", value);

		if (written > 0)
		{
			p_cursor += written;
			remaining -= static_cast<size_t>(written);
		}
	}

	template <typename... Args>
	void Write_Variadic(const char* p_level, const char* p_fmt,
		Args&&... args) noexcept
	{
		if (p_fmt == nullptr)
			return;

		char formatted[1024]{};
		char* p_cursor = formatted;
		size_t remaining = sizeof(formatted) - 1;
		const char* p_fmt_cursor = p_fmt;

		consume_all(p_fmt_cursor, p_cursor, remaining, args...);

		// the fmt tail after the last placeholder
		if (*p_fmt_cursor != '\0')
		{
			append_arg(p_cursor, remaining, p_fmt_cursor);
		}

		this->Write(p_level, formatted);
	}

private:
	static void consume_all(const char*&, char*&, size_t&) noexcept {}

	// each {} consumes the next argument in order (the only placeholder
	// shape the engine's macros emit); stateless recursion — MSVC's parser
	// rejects the fold-expression form over a generic lambda
	template <typename T, typename... Rest>
	static void consume_all(const char*& p_fmt, char*& p_cursor,
		size_t& remaining, T&& first, Rest&&... rest) noexcept
	{
		const char* p_placeholder = strstr(p_fmt, "{}");

		if (p_placeholder != nullptr)
		{
			const size_t prefix_length =
				static_cast<size_t>(p_placeholder - p_fmt);
			if (prefix_length < remaining)
			{
				memcpy(p_cursor, p_fmt, prefix_length);
				p_cursor += prefix_length;
				remaining -= prefix_length;
			}

			append_arg(p_cursor, remaining, first);
			p_fmt = p_placeholder + 2;
		}

		consume_all(p_fmt, p_cursor, remaining, rest...);
	}

	void Write(const char* p_level, const char* p_text) noexcept
	{
		if (p_text == nullptr)
			return;

		std::lock_guard<std::mutex> lock(this->m_write_mutex);

		std::time_t now = std::time(nullptr);
		std::tm local_tm{};
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		localtime_s(&local_tm, &now);
#else
		localtime_r(&now, &local_tm);
#endif

		char line[1024];
		const int line_length = snprintf(line, sizeof(line),
			"[%04d-%02d-%02d %02d:%02d:%02d] [%s] %s\n",
			local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday,
			local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec, p_level,
			p_text);

		if (line_length <= 0)
			return;

		// snprintf returns the WOULD-BE length on truncation — clamping is
		// mandatory: using the would-be length as a byte count reads past
		// the buffer
		const size_t safe_length = static_cast<size_t>(
			line_length < static_cast<int>(sizeof(line) - 1)
				? line_length
				: static_cast<int>(sizeof(line) - 1));

#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_file_handle)
		{
			DWORD written = 0;
			WriteFile(this->m_file_handle, line,
				static_cast<DWORD>(safe_length), &written, nullptr);

			// errors must hit the disk when they happen, not on a later
			// flush
			if (p_level[0] == 'e')
			{
				FlushFileBuffers(this->m_file_handle);
			}

			this->m_bytes_written += written;

			// bounded by design: rotate instead of growing without end
			if (this->m_bytes_written >= KOTEK_DEF_CUSTOM_LOG_MAX_FILE_SIZE)
			{
				this->Rotate();
			}
		}
#else
		if (this->m_p_file)
		{
			fwrite(line, 1, safe_length, this->m_p_file);

			// errors must hit the disk when they happen, not on a later
			// flush — the rest rides the C runtime's buffer
			if (p_level[0] == 'e')
			{
				fflush(this->m_p_file);
			}
		}
#endif

		fputs(line, stdout);

#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_to_debug_window)
		{
			OutputDebugStringA(line);
		}
#endif
	}

private:
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	// single-generation rotation: <path> -> <path>.prev (overwritten), then
	// a fresh file — the log never exceeds ~2x the cap on disk
	void Rotate(void) noexcept
	{
		if (this->m_file_handle)
		{
			CloseHandle(this->m_file_handle);
			this->m_file_handle = nullptr;
		}

		if (this->m_file_path[0] != '\0')
		{
			char previous_path[KOTEK_DEF_CUSTOM_LOG_PATH_MAX + 8]{};
			strncpy_s(previous_path, this->m_file_path, _TRUNCATE);
			strncat_s(previous_path, ".prev", _TRUNCATE);
			// MoveFileExA, not MoveFileA-with-flags: the 3-arg MoveFileA only
			// exists for _WIN32_WINNT >= 0x0600 and parts of this tree
			// target XP-level headers
			MoveFileExA(this->m_file_path, previous_path,
				MOVEFILE_REPLACE_EXISTING);

			this->m_file_handle = CreateFileA(this->m_file_path,
				FILE_APPEND_DATA, FILE_SHARE_READ, nullptr, OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, nullptr);

			if (this->m_file_handle == INVALID_HANDLE_VALUE)
			{
				this->m_file_handle = nullptr;
			}
		}

		this->m_bytes_written = 0;
	}
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	HANDLE m_file_handle = nullptr;
	char m_file_path[KOTEK_DEF_CUSTOM_LOG_PATH_MAX]{};
	size_t m_bytes_written = 0;
#else
	std::FILE* m_p_file = nullptr;
#endif
	bool m_to_debug_window = false;
	std::mutex m_write_mutex;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
