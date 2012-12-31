#!/usr/bin/ruby
def ack(m, n)
  return n + 1 if m == 0
  return ack m - 1, 1 if n == 0 and m > 0
  return ack m - 1, ack(m, n - 1) if n > 0 and m > 0
end

n = 0
while(true) do
  ack(3, n)
  puts "Last successful number: #{n}"
  n += 1
end
