require 'mkmf'

have_library 'stdc++'

dir_config('rubicable')

$srcs = %w[rubicable.c]

with_cflags('-x c++') do
  create_makefile 'rubicable'
end
