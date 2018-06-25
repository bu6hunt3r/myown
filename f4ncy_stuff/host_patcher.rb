#!/usr/bin/env ruby
#coding: utf-8

require 'optparse'

options={}

ARGV << "-h" if ARGV.empty?

parser=OptionParser.new {|opts|
	opts.banner="Usage: $0 [-l|-r]"
	opts.on("-l", "--localhost", "Patch to localhost") do |l|
		options[:localhost]=true
	end
	opts.on("-r", "--remote", "Patch to remote host") do |r|
		options[:remote]=true
	end
}.parse!

if (options[:localhost] and options[:remote]) then
	puts "only one option is allowed"
	exit 0
elsif !(options[:localhost] ^ options[:remote]) then
	puts "need at least on argument"
	exit 0
end

if not Process.uid.zero? then puts "Must run as superuser"; exit 0 end

pwn3=`dig pwn3.mobile.org +short`

buf=File.read("/etc/hosts")

if options[:localhost]
	File.open("/etc/hosts","w") {|file| file.print buf.gsub(/#{pwn3.gsub(/\./,"\\.").chomp!}/,"127.0.0.1")}
	puts "To localhost"
else
	File.open("/etc/hosts","w") {|file| file.print buf.gsub(/127\.0\.0\.1/,"#{pwn3.chomp!}")}
	puts "To remote"
end


