#!/usr/bin/ruby
def parse_file(input_name)
  pattern = /(\+1)\s(\([2-9][0-9]{2}\)\s|[2-9][0-9]{2}\s\-\s)[2-9][0-9]{2}\s\-\s[0-9]{4}/
  
  input_file = File.new input_name, 'r'
  phone_op = File.new 'PhoneOP.txt', 'w'
  pat_op = File.new 'PatOp.txt', 'w'
  
  phone_op.print "Input file:: #{input_name}\n"
  phone_op.print "Patern:: #{pattern.to_s}\n\n"
  
  input_file.each do |line|
    match_object = pattern.match(line)
    if match_object
      phone_op.print "#{match_object}\n"

      pat_op.print "All patterns::\n"
      pat_op.print " $` = #{$`}\n"
      pat_op.print " $& = #{$&}\n"
      pat_op.print " $' = #{$'}\n"
      pat_op.print " $~ = #{$~}\n"
      pat_op.print " $1: #{$1}\n\n"
    end
  end
end

parse_file("PhoneIP.txt")
