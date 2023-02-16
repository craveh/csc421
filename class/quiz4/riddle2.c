#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char * argv[]) {
	char options[5] = "-" ;
	int ch ;
	while ((ch=getopt(argc, argv,"v"))!=-1) {
		switch(ch) {
			case 'v':
				strcat(options,"v") ;
				break ;
			dafault:
				break ;
		}
	}
	return 0 ;
}

