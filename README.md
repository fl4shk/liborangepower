# Lib Orange Power
Small, generic C++17 library consisting of mainly header files, with a
notable exception that json\_stuff.cpp exists and should be compiled into
any of my projects that also use json\_stuff.hpp... or yours, if you choose
to use json\_stuff.hpp.


json\_stuff.hpp and json\_stuff.cpp rely upon jsoncpp:  https://github.com/open-source-parsers/jsoncpp


Any utility code I write that I use in more than one project is likely to
end up in this library.



What I use the most from this library is #included in
  examples/example\_misc\_includes/misc\_includes.hpp
mainly for my own convenience so I don't have to re-type its contents.
