#!/usr/bin/env ruby

require 'netaddr'
require 'optparse'

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
	puts "Processing #{i}/#{line_count}"
	range=line.strip.split(/\s*-\s*/)
	lower=range[0]
	upper=range[1]
	puts "upper: #{upper}; lower: #{lower}"
	ip_net_range = NetAddr.range(lower, upper, :Inclusive => true, :Objectify => true)
	cidrs = NetAddr.merge(ip_net_range, :Objectify => true)
	outfile.write("#{cidrs.network}/#{cidrs.netmask}")
end

# Todo:
# figlet
# GeoIp
# Progress Bar
