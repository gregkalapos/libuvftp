#pragma comment (lib, "libuv.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Iphlpapi.lib")


#include <iostream>
//#include <stdio.h>
#include <string.h>
//#include <unistd.h>
//#include <io.h>
#include <uv.h>

uv_loop_t *loop;
uv_tty_t tty;
int main() {
	loop = uv_default_loop();

	uv_tty_init(loop, &tty, 1, 0);
	uv_tty_set_mode(&tty, UV_TTY_MODE_NORMAL);

	// Set as cyan text on blue background
	if (uv_guess_handle(1) == UV_TTY) {
		uv_write_t req;
		uv_buf_t buf;
		//buf.base = "\033[41;37m";
		buf.base = "\033[44;36m";
		buf.len = strlen(buf.base);
		uv_write(&req, (uv_stream_t*)&tty, &buf, 1, NULL);
	}

	// Spit out the text
	uv_write_t req;
	uv_buf_t buf;
	buf.base = "Hello TTY\n";
	buf.len = strlen(buf.base);
	uv_write(&req, (uv_stream_t*)&tty, &buf, 1, NULL);

	// Reset any ANSI styles from above
	if (uv_guess_handle(1) == UV_TTY) {
		uv_write_t req;
		uv_buf_t buf;
		buf.base = "\033[0m";
		buf.len = strlen(buf.base);
		uv_write(&req, (uv_stream_t*)&tty, &buf, 1, NULL);
	}

	uv_tty_reset_mode();
	return uv_run(loop, UV_RUN_DEFAULT);

	return 0;
}