require 'mkmf'

have_library 'stdc++'

dir_config('tester')

with_cflags('-x c++') do
  create_makefile 'tester'
end

