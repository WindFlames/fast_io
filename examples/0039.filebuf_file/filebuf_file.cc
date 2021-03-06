#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy_impl/cpp/filebuf_file.h"

int main()
{
	fast_io::filebuf_file fb("filebuf_file.txt",fast_io::open_mode::binary|fast_io::open_mode::out);
	std::ostream out(fb.rdbuf());
	out<<"Hello world from std::ostream\n";
	print(fb,"Hello World from fast_io\n");
	out<<"Hello world from std::ostream again\n";
	print(fb,"Hello World from fast_io again\n");
}