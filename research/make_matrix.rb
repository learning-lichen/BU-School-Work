f = File.new 'O7_ctd.csv', 'r'

begin
  while line = f.readline
    puts line + " my ending\n"
  end 
rescue IOError
  f.close
end
