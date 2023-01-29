#!/usr/bin/perl
# Parses a file (currently /etc/os-release) to extract distro information
# then uses that information to select the right set of packages to install

use strict;
use warnings;
use Term::ANSIColor qw(:constants);

################INSTALLATION SUBROUTINES################

sub ubuntu{
	# Subroutine to install stuff on Ubuntu. Use apt
	print RED BOLD, "Ubuntu detected\n", RESET;
	system("sudo apt update && sudo apt install python3 virtualenv clang-format cppcheck");
}

sub fedora{
	# Install on Fedora. Use dnf
	print BLUE BOLD, "Fedora detected\n", RESET;
	system("sudo dnf install python3 virtualenv clang-tools-extra cppcheck");
}

sub rhel{
	# Same as Fedora, for now. Might use EPEL later.
	print RED BOLD, "RHEL detected\n", RESET;
	fedora();
}

sub arch{
	# Install all packages via pacman except for clang-format. Grab the statically linked binary from aur
	print BLUE BOLD, "Arch BTW detected\nNOTE: requires yay AUR helper\n", RESET;
	system("sudo pacman -Syyu && sudo pacman -S python python-virtualenv cppcheck yay && yay -S clang-format-static-bin ");
}

sub debian{
	# Package names are same as Ubuntu
	print GREEN BOLD, "Debian detected\n", RESET;
	ubuntu();
}

sub gentoo{
	# Use emerge --pretend --verbose; install required packages. clang-format is included with clang by default, I think
	print BLUE BOLD, "Gentoo detected. wtf\n", RESET;
	system("emerge -pv dev-lang/python dev-python/virtualenv sys-devel/clang dev-util/cppcheck");
}

################PARSER################

# File to parse. Change this if something breaks.
# On most systems, the first line of /etc/os-release will be something like this: NAME="Fedora Linux"
# Also details a bunch of other information about the distro
my $f = '/etc/os-release';

if( -e $f){	# if file exists
	print("Parsing $f...\n"); # print it so user knows which file is selected
	open my $fr, '<', $f; # Open it for reading
	my $line = <$fr>; # read first line
	#print("$line\n");
	#$line = chomp($line);
	#print("$line\n");
	$line = lc $line; # convert to lowercase
	close $fr; # close file
	# Print some helpful information, and allow the user to skip package installation if necessary without triggering
	# an error, which would make the bloop-dev script exit.
	print("$line\nThe setup script needs to install some required components for the build process\nIt will attempt to install them now. If your account does not have sudo access\nplease speak to your system administrator and have them install the packages listed here: (listed for ubuntu and derivatives)\n", GREEN BOLD ,"python3 virtualenv clang-format cppcheck",RESET,"\nInstall now? [Y/n]: ");
	my $k = getc(STDIN); # get a character from stdin
	if($k eq 'n'){		#If it's the letter n, skip package installation. User is assumed to have them installed already (and possibly using an unsupported distro or an account without sudo access)
		print("User selected ",BOLD RED,"NO",RESET,", assuming packages are already installed\n");
		exit(0); # clean exit
	}
	# check to see if $line contains the distro name, then call the apropriate subroutine
	if(index($line, 'fedora') != -1){
		fedora();
	}elsif(index($line, 'ubuntu') != -1){
		ubuntu();
	}elsif(index($line, 'rhel') != -1){
		rhel();
	}elsif(index($line, 'arch') != -1){
		arch();
	}elsif(index($line, 'debian') != -1){
		debian();
	}elsif(index($line, 'gentoo') != -1){
		gentoo(); # ?
	}else{
		# exit with error - bloop-dev calls this with an || exit 1 behind it so this makes it exit too.
		# If we haven't installed the required packages, the rest of the stuff (which is left in bloop-dev) won't work
		die("OS not supported yet! Please bother Michael or add it here");
	}
}else{
	# Give a helpful error message if it can't find the file to parse
	print("[",BOLD RED, "ERROR",RESET,"]", "Could not find $f, make sure that $f exists and that you are on a Linux platform.\n");
	die("Unsupported platform\n");
}
