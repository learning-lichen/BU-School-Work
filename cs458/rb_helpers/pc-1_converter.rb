# NOTE: Row value = (7 * row_number) + 1

ip_matrix = Array.new(8)
ip_matrix[0] = [32, 1, 2, 3, 4, 5]
ip_matrix[1] = [4, 5, 6, 7, 8, 9]
ip_matrix[2] = [8, 9, 10, 11, 12, 13]
ip_matrix[3] = [12, 13, 14, 15, 16, 17]
ip_matrix[4] = [16, 17, 18, 19, 20, 21]
ip_matrix[5] = [20, 21, 22, 23, 24, 25]
ip_matrix[6] = [24, 25, 26, 27, 28, 29]
ip_matrix[7] = [28, 29, 30, 31, 32, 1]

key = "11110000101010101111000010101010".split(//)
ip = Array.new(48)
key_position = 0

ip_matrix.each do |matrix_row|
  matrix_row.each do |perm|
    ip[key_position] = key[perm - 1]
    key_position += 1
  end
end

key_position = 0
ip_out = ""

ip = "011100010001011100110010111000010101110011110000".split(//)

ip.each do |k|
  ip_out << k
  key_position += 1
  ip_out << " " if key_position % 4 == 0
end

p ip_out
