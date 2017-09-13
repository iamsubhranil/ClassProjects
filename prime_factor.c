/*   ClassProjects : A collection of all class homeworks and projects
 *   Copyright (C) 2017  Subhranil Mukherjee (https://github.com/iamsubhranil)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, version 3 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

int main(){
    int a, i, j, temp, isprime;
    printf("\nEnter the number : ");
    scanf("%d", &a); // Input the number
    printf("\nThe prime factors of %d are :", a);
    for(i = a/2; i >= 2; i--){ // Search for factors of `a`
        if(a % i == 0){ // `i` is a factor of `a`
            temp = i; // Store it to a temporary variable
            isprime = 1; // prime flag
            for(j = 2; j <= temp/2; j++){ // Search for factors of `temp`
                if(temp % j == 0){ // Factor of `temp` is found
                    isprime = 0; // `temp` is not prime
                    break;
                }
            }
            if(isprime) // `temp` is prime
                printf(" %d", i);
        }
    }
    return 0;
}
