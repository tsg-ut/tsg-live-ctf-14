#!/usr/bin/env perl
use Dancer2;

set template => 'template_toolkit';

get '/' => sub {
    return template 'index';
};

post '/echo' => sub {
    my $str = body_parameters->get('str');
    unless (defined $str) {
        return "No input provided";
    }

    if ($str =~ /[&;<>|\(\)\$\ ]/) {
        return "<h2>echo:</h2><pre>Invalid Input</pre><a href='/'>Back</a>";
    };

    my $output = `echo $str`;

    return "<h2>echo:</h2><pre>$output</pre><a href='/'>Back</a>";
};

start;
