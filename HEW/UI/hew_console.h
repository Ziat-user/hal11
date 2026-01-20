// hew_console.h
#ifndef HEW_CONSOLE_SLIM_C_ONLY_H
#define HEW_CONSOLE_SLIM_C_ONLY_H

/*
  HEW Console Library - Minimal C-only Public Header
  --------------------------------------------------
  Purpose: Provide the smallest C interface for projects that do NOT need
		   C++ wrappers or DLL import/export macros.

  API:
	int hew_console_start(int monitor_index);
	int hew_console_restore(void);

  Notes:
	- monitor_index: primary-first ordering (0 = primary). Pass -1 for auto (nearest).
	- Both functions return 0 on success; see project docs for error codes.
*/

#ifdef __cplusplus
extern "C" {
#endif

	int hew_console_start(int monitor_index);
	int hew_console_restore(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* HEW_CONSOLE_SLIM_C_ONLY_H */