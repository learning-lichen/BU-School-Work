require 'inline'
class Tester
  inline(:C) do |builder|
    builder.include '<iostream>'
    builder.add_compile_flags '-x c++', '-lstdc++'
    builder.c '
      void hello(int i) {
        while (i-- > 0) {
          std::cout << "hello world" << std::endl;
        }
      }'
    end
end

t = Tester.new
t.hello(3)
