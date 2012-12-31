class Tester
  def method_missing(symbol, *args)
    symbol
  end
end
