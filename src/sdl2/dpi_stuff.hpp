#ifndef liborangepower_sdl2_dpi_stuff_hpp
#define liborangepower_sdl2_dpi_stuff_hpp


namespace liborangepower
{

namespace sdl
{

void handle_dpi()
{
	#ifdef __WIN32__
		//On Vista or newer windows, let the OS know we are DPI aware, so we
		//won't have odd scaling issues.
		void* user_dll = SDL_LoadObject("USER32.DLL");
		if (user_dll)
		{
			BOOL(WINAPI *SetProcessDPIAware)(void);
			SetProcessDPIAware = reinterpret_cast<BOOL(WINAPI *)(void)>
				(SDL_LoadFunction(user_dll, "SetProcessDPIAware"));
			if (SetProcessDPIAware)
				SetProcessDPIAware();
		}

		//Move the console window to the top left corner, makes it easier to
		//read the log output in debug mode.
		HWND console_handle = GetConsoleWindow();
		if (console_handle)
			SetWindowPos(console_handle, nullptr, 0, 0, 0, 0, 
				SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE 
				| SWP_NOZORDER);
	#endif // __WIN32__
}

} // namespace sdl

} // namespace liborangepower

#endif		// liborangepower_sdl2_dpi_stuff_hpp
