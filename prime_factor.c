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
    scanf("%d", &a);
    printf("\nThe prime factors of %d are :", a);
    for(i = 2; i <= a/2; i++){
        if(a % i == 0){
            temp = i;
            isprime = 1;
            for(j = 2; j <= temp/2; j++){
                if(temp % j == 0){
                    isprime = 0;
                    break;
                }
            }
            if(isprime)
                printf(" %d", i);
        }
    }
    return 0;
}
