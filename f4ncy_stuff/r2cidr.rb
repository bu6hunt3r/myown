#!/usr/bin/env ruby

require 'netaddr'
require 'optparse'

Banner=%q{
        ____      _     _      
    _ _|___ \ ___(_) __| |_ __ 
   | '__|__) / __| |/ _` | '__|
   | |  / __/ (__| | (_| | |   
   |_| |_____\___|_|\__,_|_|						   
}

puts Banner
options={}
OptionParser.new do |opt|
	opt.on('--ranges PATH'){|r| options[:ranges]=r}
	opt.on('--cidr PATH'){|c| options[:cidr]=c}
end.parse!

outfile=File.open(options[:cidr],'a')

line_count = `wc -l "#{options[:ranges]}"`.strip.split(' ')[0].to_i

i=0

File.readlines(options[:ranges]).each do |line|
	i+=1
	range=line.strip.split(/\s*-\s*/)
	lower=range[0]
	upper=range[1]
	print "\r\033[4;31mProcessing\033[0m #{(i/line_count)*100}%".ljust(20)+"\tupper: #{upper}; lower: #{lower}".ljust(50)
	$stdout.flush
	ip_net_range = NetAddr.range(lower, upper, :Inclusive => true, :Objectify => true)
	cidrs = NetAddr.merge(ip_net_range, :Objectify => true)
	outfile.write("\n#{cidrs[0]}")
end

# Todo:
# figlet
# GeoIp
# Progress Bar
