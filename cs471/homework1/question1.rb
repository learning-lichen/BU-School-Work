#!/usr/bin/ruby
def gcdR(i, j)
  return i if i == j
  return gcdR i % j == 0 ? j : i % j, j if i > j
  return gcdR i, j % i == 0 ? i : j % i
end

puts "The GCD of 100 and 247 is #{gcdR(100, 247)}"
puts "The GCD of 16 and 32 is #{gcdR(16, 32)}"
puts "The GCD of 22 and 3456 is #{gcdR(22, 3456)}"
