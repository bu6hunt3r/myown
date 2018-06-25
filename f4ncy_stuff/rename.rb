#!/usr/bin/env ruby

require 'optparse'

ARGV << "--help" if ARGV.empty?

options={:infile => nil, :outdir => nil}
ARGV.options do |opts|
    opts.banner="Usage: rename.rb -i [INPUT FILE NAME CONTAINING NAMES] -o [WORKING DIR] -p [PATTERN TO OPERATE ON]"
    opts.on('-i','INPUT FILE NAME CONTAINING NAMES') {|infile|
        options[:infile]=infile;
    }
    opts.on('-o','WORKING DIR') {|outdir|
        options[:outdir]=outdir;
    }
    opts.on('-p','PATTERN TO OPERATE ON') { |pattern|
        options[:pattern] = pattern;
    }
    opts.on('-h','--help','Display this screen') do 
        puts opts
        exit
    end
    opts.parse!
end

options.each_pair do |key, value|
    puts "key is #{key}"
  puts "value is #{value}"
end
