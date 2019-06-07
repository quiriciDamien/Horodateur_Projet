/*
 * decim_to_bin.c
 *
 *  Created on: 6 juin 2019
 *      Author: damien
 */
int decimal_binary(int n){
	int rem, i=1, binary =0;
	while(n!=0){
		rem=n%2;
		n=n/2;
		binary=binary+rem*i;
		i=i*10;
	}
	return binary;
}

