/* original author: anthony_sully */
/* EX_site_CAP_COMPARE.c */
/* adapted from Fusion HF to Fusion EX adapter board converter */
/* 04/02/07 - original rev. APS */
/* 2007/08/18 - updated for capacitance calculations and add command call (EX_TO_HF) for inverting back to HFi */
//
// Compile with gcc -Wall -ggdb HF_TO_EX4.c -o HF_TO_EX
// Create Links:
// ln -s HF_TO_EX HF_TO_EX_HC      (for high current conversions)
//
// Other potential links:
// RASPCAP    include computations for RASP/BAPS digital pin capacitances based on internal table
// HFICAP     include computations for HF adapter digital pin capacitances based on internal table
// EX_TO_HF   for backwards mapping
//


#define DEBUG 0

#ifndef __TIME__
#define  __TIME__ "notime like the present"
#define __DATE__ " Thurs June 02 09:44:30 PDT 2005 "
#endif

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>
#define MEMOSTRLEN 120
#define MAXSITE 16
#define MAXPIN 512
#define MAXBOARD 4
#define NAMELEN 100

float AVECAPLB[] = {110.47,111.18,111.33,107.17,109.18,103.31,105.89,105.17,105.03,100.44,100.30, 95.14, 98.01, 93.57, 97.58, 94.28, /*000 */
                    109.47,109.75,111.18,105.74,108.46,100.73,106.17,101.45,104.74, 99.44, 98.15, 96.29, 96.86, 91.71, 98.01, 91.56, /*016 */
                    111.61,111.33,115.34,109.61,110.90,103.02,106.03,103.59,106.03,101.59,103.59, 98.15, 97.86, 95.00,103.45, 94.71, /*032 */
                    115.77,113.48,115.34,108.46,110.33,102.73,109.61,104.31,106.32, 99.58, 99.58, 98.58, 99.73, 93.28,103.45, 94.71, /*048 */
                    116.48,111.76,116.20,110.76,111.61,104.60,108.75,106.17,108.32,102.73,103.59, 99.01,100.59, 94.86, 99.87, 99.15, /*064 */
                    114.48,111.76,115.05,109.61,111.61,103.59,106.17,104.74,107.32,100.30,102.59, 99.58, 99.87, 96.15,100.59, 95.57, /*080 */
                    117.06,115.63,120.49,112.90,116.05,105.31,113.76,108.75,112.90,104.17,105.89,101.16,106.03, 96.29,106.32, 97.58, /*096 */
                    113.76,114.77,117.92,111.33,113.19,108.32,109.75,106.32,108.89,104.31,103.88,101.30,101.45, 98.15,106.74, 98.72, /*112 */
                    108.46,108.89,110.90,105.60,108.46, 99.73,103.45,103.02,104.31, 99.30, 99.58, 93.57, 98.01, 90.99, 96.29, 91.71, /*128 */
                    109.75,109.90,110.90,106.89,107.89,100.59,105.60,101.16,104.45,100.01, 98.58, 95.86, 97.01, 91.99, 98.29, 91.85, /*144 */
                    112.19,112.33,115.62,110.04,110.61,103.45,106.03,103.74,104.45,100.44,104.02, 99.01, 97.72, 95.43,102.45, 94.86, /*160 */
                    114.91,112.04,114.62,107.46,107.46,101.45,108.61,103.74,104.88, 98.29, 99.44, 97.43, 98.87, 92.28,102.02, 94.00, /*176 */
                    114.19,108.75,115.20,108.89,110.61,102.16,106.46,102.59,106.89,100.16,101.16, 97.29, 99.58, 94.14, 98.58, 97.29, /*192 */
                    113.19,109.47,113.05,108.46,110.61,103.45,105.89,103.88,105.17, 97.86,101.30, 97.72, 99.01, 94.28, 99.15, 94.43, /*208 */
                    116.77,115.48,119.64,112.19,115.05,105.89,113.48,108.32,111.47,104.45,106.32,100.44,105.60, 96.43,105.31, 97.01, /*224 */
                    113.05,113.62,116.34,110.18,112.33,107.32,109.47,106.32,107.89,103.16,102.30,100.16,100.59, 96.43,106.17, 99.15, /*240 */
                    109.75,110.90,111.47,106.74,108.89,102.59,104.88,104.88,104.31,100.30, 99.58, 94.71, 98.29, 93.28, 96.29, 94.14, /*256 */
                    112.04,112.33,114.19,109.61,111.33,103.31,107.60,104.60,107.60,103.02,101.73, 97.86, 98.44, 94.43,100.44, 93.85, /*272 */
                    112.90,114.34,115.48,110.61,112.62,105.31,108.03,104.31,107.17,103.16,104.88, 98.58, 98.58, 96.72,104.60, 96.72, /*288 */
                    115.48,113.19,115.20,109.04,110.04,101.59,110.76,104.31,106.46, 98.72,100.16, 97.15, 99.58, 92.57,102.59, 94.28, /*304 */
                    116.48,111.61,115.77,110.18,111.18,104.02,109.04,105.74,107.60,102.16,102.88, 99.44,100.44, 95.57, 99.87, 98.58, /*320 */
                    117.49,113.76,116.05,111.18,113.19,106.46,109.61,107.32,107.89,101.30,103.31,100.87,100.44, 96.86,102.30, 97.01, /*336 */
                    115.48,115.91,120.35,112.90,115.05,105.89,114.19,108.46,112.04,105.46,106.89,101.73,105.17, 96.58,106.74, 98.29, /*352 */
                    114.77,116.05,119.06,113.19,113.76,109.18,111.76,108.03,109.61,104.31,103.74,101.59,102.16, 98.01,106.32,100.44, /*368 */
                    110.47,110.61,111.90,107.60,110.61,102.30,106.46,105.89,106.60,102.02,101.16, 96.86, 99.01, 92.85, 97.44, 95.29, /*384 */
                    109.90,111.18,111.33,108.03,110.33,102.45,107.17,102.45,105.89,100.87, 99.58, 97.01, 97.72, 92.57, 98.72, 92.28, /*400 */
                    112.76,112.47,115.34,110.18,111.18,104.02,107.75,104.60,106.60,102.02,104.17, 98.58, 99.01, 95.72,103.88, 95.57, /*416 */
                    114.91,112.33,116.20,108.46,109.47,102.30,110.04,105.31,105.60, 99.01, 99.30, 96.86, 99.73, 93.14,102.45, 94.43, /*432 */
                    115.77,110.33,115.77,109.32,110.18,103.16,108.03,105.46,106.46,101.45,102.16, 99.44,100.01, 95.29, 99.87, 98.44, /*448 */
                    115.20,111.47,114.77,109.47,112.04,104.45,106.74,104.45,106.74, 99.44,101.02, 98.58, 99.30, 95.72,100.16, 95.43, /*464 */
                    115.62,115.34,118.78,112.76,113.76,105.31,112.90,108.18,110.90,104.31,105.31,100.30,104.60, 96.15,104.88, 97.29, /*480 */
                    116.20,117.20,120.49,113.48,115.34,110.04,112.76,108.32,110.18,105.03,104.17,101.73,102.45, 98.29,106.60,100.30};/*496*/
/* based on EX channel numbers */
float AVECAP_TOWER[] = { 
                     97.72, 97.86, 98.15, 92.71, 96.29, 89.70, 92.85, 91.85, 91.71, 87.55, 86.98, 81.39, 85.26, 79.96, 84.83, 80.82, /*000 */
                     95.43, 95.72, 97.43, 92.57, 95.00, 86.98, 92.14, 87.55, 91.42, 86.12, 84.83, 82.54, 82.97, 78.24, 84.69, 77.96, /*016 */
                     97.86, 97.86,101.88, 96.58, 97.43, 89.27, 92.57, 90.13, 92.57, 88.13, 90.27, 85.40, 84.83, 82.11, 90.70, 82.11, /*032 */
                    102.59,100.01,101.45, 94.86, 96.43, 88.98, 96.29, 91.13, 92.42, 85.69, 86.41, 84.83, 86.26, 79.53, 90.13, 81.54, /*048 */
                    103.31, 98.87,102.88, 97.43, 98.44, 91.42, 95.29, 92.42, 95.43, 89.41, 90.27, 86.26, 87.84, 82.11, 86.84, 86.12, /*064 */
                    101.02, 97.58,100.87, 95.43, 98.29, 90.42, 92.71, 90.85, 93.28, 86.41, 88.41, 85.55, 85.98, 82.11, 86.98, 81.68, /*080 */
                    103.02,102.73,107.17, 99.58,102.59, 92.42,100.59, 95.43, 99.73, 90.99, 92.85, 88.12, 92.85, 83.26, 93.42, 84.11, /*096 */
                     99.44,100.73,103.59, 98.01, 99.30, 94.00, 97.01, 92.99, 95.43, 90.70, 90.13, 87.84, 87.70, 84.54, 92.57, 85.55, /*112 */
                     95.14, 95.14, 97.43, 92.28, 95.00, 87.12, 89.99, 89.99, 91.56, 86.26, 86.84, 80.96, 85.26, 78.39, 83.11, 79.67, /*128 */
                     95.72, 96.00, 96.86, 92.85, 94.00, 86.84, 91.85, 87.70, 91.42, 86.26, 85.26, 83.11, 83.97, 78.53, 84.69, 78.10, /*144 */
                     98.58, 99.44,101.59, 96.00, 96.43, 89.70, 92.28, 90.42, 92.42, 87.84, 90.42, 84.11, 83.97, 82.25, 88.98, 81.39, /*160 */
                    101.59, 98.58,101.59, 94.57, 94.57, 87.98, 95.29, 90.27, 91.28, 84.83, 85.98, 84.26, 85.55, 79.10, 88.27, 80.68, /*176 */
                    101.02, 95.00,101.02, 95.86, 96.86, 88.70, 93.28, 89.56, 93.28, 86.98, 88.55, 84.83, 86.41, 80.82, 85.69, 84.83, /*192 */
                     99.44, 96.43, 99.15, 94.71, 96.72, 89.84, 92.14, 89.99, 91.85, 84.40, 87.55, 83.97, 84.97, 81.25, 85.26, 81.25, /*208 */
                    102.88,101.87,106.17, 99.30,101.87, 92.28,100.30, 95.29, 97.86, 91.71, 92.42, 87.84, 92.85, 83.26, 91.99, 83.83, /*224 */
                     99.30, 99.44,102.16, 96.29, 98.58, 93.28, 95.57, 93.14, 94.14, 89.41, 88.41, 87.12, 86.98, 82.97, 92.71, 85.12, /*240 */
                     96.00, 97.15, 98.01, 93.71, 95.29, 88.98, 91.85, 91.85, 91.13, 86.55, 86.69, 81.54, 84.69, 79.82, 83.54, 81.25, /*256 */
                     97.86, 98.44, 99.44, 95.86, 97.29, 88.70, 93.85, 89.27, 93.14, 89.13, 87.98, 84.26, 85.12, 80.82, 86.98, 80.10, /*272 */
                     99.44,100.73,102.59, 96.86, 99.15, 91.28, 94.86, 90.99, 93.57, 89.56, 91.28, 84.97, 85.69, 82.68, 90.70, 82.83, /*288 */
                    101.45, 98.87,100.87, 95.29, 96.00, 87.70, 96.00, 91.13, 92.71, 85.26, 85.98, 83.83, 85.83, 79.67, 88.84, 81.11, /*304 */
                    103.31, 98.29,102.73, 96.86, 97.86, 90.56, 95.86, 92.71, 94.57, 88.98, 89.41, 86.12, 87.70, 82.68, 86.55, 85.55, /*320 */
                    102.73,100.01,101.88, 97.01, 98.87, 92.14, 95.43, 93.42, 93.57, 87.55, 89.13, 86.98, 86.84, 83.26, 87.84, 82.97, /*336 */
                    102.59,102.45,106.74, 99.73,102.16, 92.71,101.02, 95.14, 98.87, 91.99, 93.14, 88.41, 92.57, 83.40, 92.99, 85.40, /*352 */
                    100.87,102.30,103.74, 98.72,100.01, 95.14, 97.86, 94.28, 95.86, 90.27, 89.70, 88.13, 87.98, 84.40, 92.99, 86.84, /*368 */
                     97.01, 97.01, 98.29, 93.85, 97.01, 88.84, 92.85, 92.57, 92.71, 87.98, 87.70, 83.40, 85.55, 79.82, 84.11, 82.25, /*384 */
                     96.15, 97.15, 97.58, 94.14, 95.86, 87.70, 92.71, 88.55, 91.56, 87.12, 85.55, 83.11, 83.97, 79.10, 85.40, 79.10, /*400 */
                     99.58, 99.58,101.88, 96.72, 98.15, 90.85, 94.43, 91.56, 92.99, 89.27, 91.56, 86.12, 84.69, 82.54, 90.42, 82.40, /*416 */
                    100.59, 98.58,102.02, 94.57, 95.14, 88.13, 95.86, 90.85, 91.99, 85.26, 86.12, 83.11, 85.98, 79.82, 89.13, 80.82, /*432 */
                    102.59, 97.29,102.59, 96.86, 97.29, 90.85, 94.57, 91.99, 93.71, 88.70, 89.13, 86.12, 86.98, 81.68, 86.55, 84.97, /*448 */
                    100.73, 97.29,100.44, 96.00, 97.72, 89.99, 92.57, 91.13, 92.71, 85.69, 88.27, 85.40, 85.26, 80.96, 86.26, 82.54, /*464 */
                    103.31,102.59,105.17, 98.72,101.02, 92.71,100.30, 94.86, 98.29, 91.42, 92.14, 86.98, 92.14, 83.40, 91.28, 83.68, /*480 */
                    101.73,102.45,105.89, 99.87,101.02, 95.72, 98.44, 94.00, 96.29, 91.28, 90.27, 88.12, 88.70, 84.69, 92.71, 86.41};/*496*/ ;
                    
float RASP_CAP_SHORT[]= { 
                    110.42,111.42,112.42,106.07,107.07,101.73,103.73,103.73, 99.39, 96.04, 98.39, 95.04, 96.04, 89.70, 96.04, 86.35, /*000 */
                    101.73,100.39,105.73, 99.39,100.39, 91.70, 97.04, 90.70, 95.04, 94.04, 91.70, 84.35, 87.35, 83.01, 86.35, 82.01, /*016 */
                    108.07,105.73,110.07,102.73,102.73, 95.04, 98.39, 97.04, 96.04, 92.70, 92.70, 90.70, 86.35, 85.35, 90.70, 80.01, /*032 */
                    103.73,102.73,104.73, 96.39,101.73, 92.04, 94.04, 89.70, 95.04, 90.70, 91.70, 84.35, 88.35, 83.01, 83.01, 81.01, /*048 */
                    103.73, 99.39,104.73, 96.04, 98.39, 92.04, 95.04, 91.70, 90.70, 86.35, 88.35, 82.01, 88.70, 79.67, 83.35, 75.67, /*064 */
                    106.07,105.07,104.73, 97.04,101.39, 95.04, 95.04, 90.70, 95.04, 89.70, 91.70, 83.01, 87.35, 83.35, 84.35, 82.01, /*080 */
                    109.07,109.07,103.73, 96.04, 98.39, 93.04, 94.04, 90.70, 89.70, 88.35, 91.70, 80.01, 89.70, 77.67, 81.01, 74.32, /*096 */
                    103.73,102.73,110.42,101.73,103.73, 95.04, 94.04, 91.70, 98.39, 96.04, 92.70, 86.35, 90.70, 88.35, 90.70, 85.35, /*112 */
                    112.42,109.07,114.76,107.07,105.73,102.73,103.73,103.73, 99.39, 97.04, 95.04, 97.39, 95.04, 90.70, 94.04, 86.35, /*128 */
                    101.73,100.39,106.07,100.39, 98.39, 90.70, 95.04, 90.70, 94.04, 91.70, 90.70, 89.70, 86.35, 84.01, 86.35, 83.01, /*144 */
                    107.07,105.73,107.07,100.39,101.39, 96.04, 97.39, 94.04, 95.04, 89.70, 91.70, 89.70, 86.35, 83.01, 88.70, 80.01, /*160 */
                    102.73, 98.39,101.73, 96.04, 96.04, 94.04, 92.04, 89.70, 94.04, 89.70, 88.70, 83.01, 83.35, 83.01, 91.70, 83.01, /*176 */
                    102.73,102.73,110.42,102.73, 98.39, 94.04, 94.04, 86.35, 91.70, 94.04, 90.70, 83.35, 84.01, 78.67, 80.01, 82.01, /*192 */
                    117.76,103.73,108.07,101.39,102.73, 97.04, 96.04, 90.70, 99.39, 95.04, 96.04, 84.35, 88.70, 86.35, 87.70, 84.01, /*208 */
                    099.39, 96.04,102.73, 93.04, 96.39, 87.35, 89.70, 85.35, 88.35, 85.35, 84.35, 77.67, 87.35, 76.67, 78.67, 74.32, /*224 */
                    109.07,102.73,108.07, 99.39,101.73, 94.04, 97.04, 92.70, 98.39, 96.04, 93.04, 87.35, 88.70, 86.35, 89.70, 83.01, /*240 */
                    096.04, 94.04, 97.04, 89.70, 91.70, 85.35, 87.35, 82.01, 86.35, 81.01, 87.35, 82.01, 76.67, 74.32, 75.67, 67.98, /*256 */
                    091.70, 90.70, 91.70, 83.01, 88.35, 81.01, 82.01, 78.67, 83.01, 78.67, 77.67, 71.32, 73.32, 71.32, 73.32, 64.64, /*272 */
                    096.04, 94.04, 95.04, 87.35, 92.70, 84.01, 85.35, 80.01, 86.35, 81.01, 82.01, 73.32, 78.67, 73.32, 75.32, 69.98, /*288 */
                    096.04, 94.04, 96.04, 87.35, 90.70, 86.35, 87.70, 81.01, 86.35, 84.35, 81.01, 76.67, 76.67, 74.32, 75.32, 67.98, /*304 */
                    101.73, 98.39, 99.39, 92.04, 96.04, 88.70, 90.70, 87.35, 89.70, 87.35, 91.70, 77.67, 84.01, 79.67, 80.01, 75.67, /*320 */
                    098.39, 97.04, 97.04, 89.70, 94.04, 89.70, 89.70, 85.35, 88.35, 83.01, 83.01, 77.67, 77.67, 77.67, 78.67, 69.98, /*336 */
                    110.42,109.07,110.42,101.39,108.07, 99.39,108.07, 93.04, 99.39, 98.04,101.39, 86.35, 93.04, 88.70, 90.70, 84.35, /*352 */
                    101.73, 99.39,100.39, 97.04, 96.04, 92.70, 91.70, 87.35, 90.70, 84.35, 85.35, 82.01, 81.01, 78.67, 81.01, 74.32, /*368 */
                    093.70, 90.70, 90.70, 84.01, 89.70, 82.01, 84.01, 78.67, 84.01, 79.67, 79.67, 70.98, 75.67, 71.32, 74.32, 69.98, /*384 */
                    097.39, 96.04, 99.39, 90.70, 97.39, 86.35, 90.70, 87.35, 88.70, 89.70, 91.70, 76.67, 87.35, 76.67, 79.67, 77.67, /*400 */
                    097.04, 94.04, 94.04, 86.35, 92.70, 83.35, 87.35, 81.01, 87.35, 82.01, 82.01, 75.32, 81.01, 72.32, 76.67, 72.32, /*416 */
                    097.39, 93.04, 94.04, 85.35, 89.70, 84.01, 85.35, 81.01, 85.01, 80.01, 82.01, 73.32, 76.67, 73.32, 74.32, 67.98, /*432 */
                    097.39, 95.04, 98.04, 90.70, 94.04, 87.35, 89.70, 83.01, 91.70, 86.35, 85.35, 75.67, 83.01, 77.67, 78.67, 75.32, /*448 */
                    101.73, 99.39, 99.39, 95.04, 99.39, 95.04, 91.70, 87.35, 89.70, 84.01, 87.35, 88.70, 80.01, 81.01, 84.35, 73.32, /*464 */
                    103.73, 98.39,107.07, 99.39, 98.39, 90.70, 92.70, 86.35, 99.39, 93.04, 89.35, 79.67, 86.35, 77.67, 79.67, 79.67, /*480 */
                    105.73,105.73,107.07,100.39,104.73,100.39, 98.39, 95.04,102.73, 91.70, 91.70, 85.35, 91.70, 87.35, 93.70, 80.01};/*496*/ ;
                    
struct HF_TO_EX {int HF,EX;};
struct HF_TO_EX ex_to_hf[512];/* invert table through code */
struct HF_TO_EX hf_to_ex[513]={
{0,368},{1,369},{2,370},{3,371},{4,372},{5,373},{6,374},{7,375},
{8,376},{9,377},{10,378},{11,379},{12,380},{13,381},{14,382},{15,383},
{16,304},{17,305},{18,306},{19,307},{20,308},{21,309},{22,310},{23,311},
{24,312},{25,313},{26,314},{27,315},{28,316},{29,317},{30,318},{31,319},
{32,256},{33,257},{34,258},{35,259},{36,260},{37,261},{38,262},{39,263},
{40,264},{41,265},{42,266},{43,267},{44,268},{45,269},{46,270},{47,271},
{48,320},{49,321},{50,322},{51,323},{52,324},{53,325},{54,326},{55,327},
{56,328},{57,329},{58,330},{59,331},{60,332},{61,333},{62,334},{63,335},
{64,240},{65,241},{66,242},{67,243},{68,244},{69,245},{70,246},{71,247},
{72,248},{73,249},{74,250},{75,251},{76,252},{77,253},{78,254},{79,255},
{80,176},{81,177},{82,178},{83,179},{84,180},{85,181},{86,182},{87,183},
{88,184},{89,185},{90,186},{91,187},{92,188},{93,189},{94,190},{95,191},
{96,128},{97,129},{98,130},{99,131},{100,132},{101,133},{102,134},{103,135},
{104,136},{105,137},{106,138},{107,139},{108,140},{109,141},{110,142},{111,143},
{112,192},{113,193},{114,194},{115,195},{116,196},{117,197},{118,198},{119,199},
{120,200},{121,201},{122,202},{123,203},{124,204},{125,205},{126,206},{127,207},
{128,496},{129,497},{130,498},{131,499},{132,500},{133,501},{134,502},{135,503},
{136,504},{137,505},{138,506},{139,507},{140,508},{141,509},{142,510},{143,511},
{144,432},{145,433},{146,434},{147,435},{148,436},{149,437},{150,438},{151,439},
{152,440},{153,441},{154,442},{155,443},{156,444},{157,445},{158,446},{159,447},
{160,384},{161,385},{162,386},{163,387},{164,388},{165,389},{166,390},{167,391},
{168,392},{169,393},{170,394},{171,395},{172,396},{173,397},{174,398},{175,399},
{176,448},{177,449},{178,450},{179,451},{180,452},{181,453},{182,454},{183,455},
{184,456},{185,457},{186,458},{187,459},{188,460},{189,461},{190,462},{191,463},
{192,112},{193,113},{194,114},{195,115},{196,116},{197,117},{198,118},{199,119},
{200,120},{201,121},{202,122},{203,123},{204,124},{205,125},{206,126},{207,127},
{208,48},{209,49},{210,50},{211,51},{212,52},{213,53},{214,54},{215,55},
{216,56},{217,57},{218,58},{219,59},{220,60},{221,61},{222,62},{223,63},
{224,0},{225,1},{226,2},{227,3},{228,4},{229,5},{230,6},{231,7},
{232,8},{233,9},{234,10},{235,11},{236,12},{237,13},{238,14},{239,15},
{240,64},{241,65},{242,66},{243,67},{244,68},{245,69},{246,70},{247,71},
{248,72},{249,73},{250,74},{251,75},{252,76},{253,77},{254,78},{255,79},
{256,336},{257,337},{258,338},{259,339},{260,340},{261,341},{262,342},{263,343},
{264,344},{265,345},{266,346},{267,347},{268,348},{269,349},{270,350},{271,351},
{272,272},{273,273},{274,274},{275,275},{276,276},{277,277},{278,278},{279,279},
{280,280},{281,281},{282,282},{283,283},{284,284},{285,285},{286,286},{287,287},
{288,288},{289,289},{290,290},{291,291},{292,292},{293,293},{294,294},{295,295},
{296,296},{297,297},{298,298},{299,299},{300,300},{301,301},{302,302},{303,303},
{304,352},{305,353},{306,354},{307,355},{308,356},{309,357},{310,358},{311,359},
{312,360},{313,361},{314,362},{315,363},{316,364},{317,365},{318,366},{319,367},
{320,208},{321,209},{322,210},{323,211},{324,212},{325,213},{326,214},{327,215},
{328,216},{329,217},{330,218},{331,219},{332,220},{333,221},{334,222},{335,223},
{336,144},{337,145},{338,146},{339,147},{340,148},{341,149},{342,150},{343,151},
{344,152},{345,153},{346,154},{347,155},{348,156},{349,157},{350,158},{351,159},
{352,160},{353,161},{354,162},{355,163},{356,164},{357,165},{358,166},{359,167},
{360,168},{361,169},{362,170},{363,171},{364,172},{365,173},{366,174},{367,175},
{368,224},{369,225},{370,226},{371,227},{372,228},{373,229},{374,230},{375,231},
{376,232},{377,233},{378,234},{379,235},{380,236},{381,237},{382,238},{383,239},
{384,464},{385,465},{386,466},{387,467},{388,468},{389,469},{390,470},{391,471},
{392,472},{393,473},{394,474},{395,475},{396,476},{397,477},{398,478},{399,479},
{400,400},{401,401},{402,402},{403,403},{404,404},{405,405},{406,406},{407,407},
{408,408},{409,409},{410,410},{411,411},{412,412},{413,413},{414,414},{415,415},
{416,416},{417,417},{418,418},{419,419},{420,420},{421,421},{422,422},{423,423},
{424,424},{425,425},{426,426},{427,427},{428,428},{429,429},{430,430},{431,431},
{432,480},{433,481},{434,482},{435,483},{436,484},{437,485},{438,486},{439,487},
{440,488},{441,489},{442,490},{443,491},{444,492},{445,493},{446,494},{447,495},
{448,80},{449,81},{450,82},{451,83},{452,84},{453,85},{454,86},{455,87},
{456,88},{457,89},{458,90},{459,91},{460,92},{461,93},{462,94},{463,95},
{464,16},{465,17},{466,18},{467,19},{468,20},{469,21},{470,22},{471,23},
{472,24},{473,25},{474,26},{475,27},{476,28},{477,29},{478,30},{479,31},
{480,32},{481,33},{482,34},{483,35},{484,36},{485,37},{486,38},{487,39},
{488,40},{489,41},{490,42},{491,43},{492,44},{493,45},{494,46},{495,47},
{496,96},{497,97},{498,98},{499,99},{500,100},{501,101},{502,102},{503,103},
{504,104},{505,105},{506,106},{507,107},{508,108},{509,109},{510,110},{511,111},{512,9999}
};

int HCOVImaptoCPS[216+16+1];
int CPStoHCOVImap[16][3]={{1,9,10},{2,137,0},{3,15,16},{4,143,0},
                   {5,73,74},{6,142,0},{7,79,80},{8,144,0},
                   {9,77,78},{10,139,0},{11,75,76},{12,141,0},
                   {13,13,14},{14,140,0},{15,11,12},{16,138,0}};

int CPStoHCOVImapHC[16][5]={{1,137,138,139,140},{2,141,142,143,144},{3,81,82,83,84},{4,85,86,87,88},
                   {5,201,202,203,204},{6,205,206,207,208},{7,17,18,19,20},{8,9,10,11,12},
                   {9,145,146,147,148},{10,149,150,151,152},{11,73,74,75,76},{12,77,78,79,80},
                   {13,209,210,211,212},{14,213,214,215,216},{15,21,22,23,24},{16,13,14,15,16}};



int main (int argc,char *argv[]){
char progstr[MEMOSTRLEN+1],datestr[MEMOSTRLEN+1];
float CAPD;
char timestr[MEMOSTRLEN+1],compilestr[MEMOSTRLEN+1];
FILE *fpin,*fpout,*fptable;
char outfile[1000],BUFFER[1000],findme[100],name[100],*ptrname;
char *sptr1,*sptr2,*sptr3,*sptr4,*sptr5,*endofbasic,*endofnormal;
int site,i,j,k,omap[17],cps[17],bracecountclose;
int RASPCAP=0,HFICAP=0,EX_TO_HF=0,HF_TO_EX_HC=0;
char powerin[10],powerout[10];
long l;

strcpy(progstr,__FILE__);
strcpy(datestr,__DATE__);
strcpy(timestr,__TIME__);
strcpy(compilestr,argv[0]);
fprintf(stderr,"\n\n%s:%s, by Anthony Sully compiled:%s\n",compilestr,progstr,datestr);
if (strstr(compilestr,"RASPCAP")!=NULL) {fprintf(stderr,"Computing RASP CAPACITANCE TABLE ONLY!\n");RASPCAP=1;}
if (strstr(compilestr,"HFICAP")!=NULL) {fprintf(stderr,"Computing HFI TOWER CAPACITANCE TABLE ONLY!\n");HFICAP=1;}
if (strstr(compilestr,"EX_TO_HF")!=NULL) {fprintf(stderr,"****Inverting**** EX board to HF!\n");EX_TO_HF=1;strcpy(powerin,"HCOVI");strcpy(powerout,"CPS");}
if (strstr(compilestr,"HF_TO_EX_HC")!=NULL) {fprintf(stderr,"High Current Adapter!\n");HF_TO_EX_HC=1;strcpy(powerin,"CPS");strcpy(powerout,"HCOVI");}
else {fprintf(stderr,"Converting HF board to EX!\n");EX_TO_HF=0;strcpy(powerin,"CPS");strcpy(powerout,"HCOVI");}

if (argc<2) {
   fprintf(stderr,"Syntax: %s file\n",compilestr);
   fprintf(stderr,"If executable is \"EX_TO_HF\" it will take an EX Board and back convert to HF\n");
   fprintf(stderr,"If executable is \"HFICAP\" or \"RASPCAP\" new board will NOT be generated, it will just give a capacitance table\n");
   fprintf(stderr,"If executable is \"HF_TO_EX_HC\" CPS to HCOVI mapping for high current adapter\n");
   exit(3);
   }
if (NULL==(fpin=fopen(argv[1],"r"))) {fprintf(stderr,"Can't open %s for reading\n",argv[1]);exit(1);}
if (HFICAP || RASPCAP) sprintf(outfile,"/dev/null");
else if (EX_TO_HF) sprintf(outfile,"HFi_%s",argv[1]);
else sprintf(outfile,"EX_%s",argv[1]);
if (NULL==(fpout=fopen(outfile,"w"))) {fprintf(stderr,"Can't open %s for writing\n",outfile);exit(1);}
sprintf(outfile,"%s.captable",argv[1]);
if (HFICAP || RASPCAP) {
	if (NULL==(fptable=fopen(outfile,"w"))) {fprintf(stderr,"Can't open %s for writing\n",outfile);exit(1);}
	}
for (i=0;i<512;i++) {ex_to_hf[hf_to_ex[i].EX].EX=hf_to_ex[i].EX;ex_to_hf[hf_to_ex[i].EX].HF=hf_to_ex[i].HF;}
for (i=0;i<=216+16;i++) HCOVImaptoCPS[i]=0;/* prefill all hcovi slots to be CPS0, real mapping will be set on next line */
for (i=1;i<=16;i++) {
	if (HF_TO_EX_HC==1) HCOVImaptoCPS[CPStoHCOVImapHC[i-1][2]]=HCOVImaptoCPS[CPStoHCOVImapHC[i-1][1]]=CPStoHCOVImapHC[i-1][0];
	else                HCOVImaptoCPS[CPStoHCOVImap  [i-1][2]]=HCOVImaptoCPS[CPStoHCOVImap  [i-1][1]]=CPStoHCOVImap  [i-1][0];
	}
HCOVImaptoCPS[0]=0;
//for (i=0;i<512;i++) fprintf(stdout,"EX:%03d,HF%03d\n",ex_to_hf[i].EX,ex_to_hf[i].HF);
//for (i=1;i<=216+16;i++) fprintf(stdout,"HCOVI%d=CPS%d\n",i,HCOVImaptoCPS[i]);

while(fgets(BUFFER,1000,fpin)!=NULL) {
if ((strstr(BUFFER,"enVision:")!=NULL) || (strstr(BUFFER,"enVisionObject:") != NULL )) {
	fprintf(fpout,"%s",BUFFER);
	continue;
	}
if ((strstr(BUFFER,"/*")!=NULL) || (strstr(BUFFER,"/*")!=NULL)) {
	fprintf(stderr,"This script requires that comments be removed before processing\n");
	fprintf(stderr,"Please make a copy of your original file and remove the comments\n");
	fprintf(stderr,"and then re-run on this new file\nExiting...\n");
	exit(2);
	}	

if (BUFFER[strlen(BUFFER)-1]=='\n') BUFFER[strlen(BUFFER)-1]='\0';
for(bracecountclose=0,i=0;i<strlen(BUFFER);i++) if(BUFFER[i]=='}') bracecountclose++;
endofnormal=strrchr(BUFFER,'}');
if (endofnormal==NULL) endofnormal=BUFFER+strlen(BUFFER);
else endofnormal++;
if ((ptrname=strstr(BUFFER,"Name"))!=NULL) {
   i=0;
   while (*ptrname!='=') ptrname++;
   ptrname++;
   while (*ptrname!=';') name[i++]=*ptrname++;
   name[i]='\0';
   }
// fprintf(stdout,"---------LINE---------\n");
//	fprintf(stdout,"%s",BUFFER);
//	fflush(stdout);
   sptr1=BUFFER;
   for (site=1;site<=16;site++) {
      cps[site]=0;
      sprintf(findme,"TesterCh[%d]",site); 
// fprintf(stdout,"<<<%s>>>\n",findme);
      if (NULL!=(sptr2=strstr(sptr1,findme))) {
         if (site==1)  endofbasic=sptr2;
         sptr3=sptr2+strlen(findme);
         sptr4=strchr(sptr3,'=');
         sptr3=sptr4;
//         fprintf(stdout,"$$%s$$\n",sptr3);
         if (sptr4==NULL) break;
         sptr3++;
         sptr4=sptr3;
         omap[site]=-1;
         l=strtol(sptr3,&sptr4,10);
         if (l>511) l=512;
         if (sptr4==sptr3) { /* cps or hcovi */
            while ((NULL!=(sptr4=strstr(sptr3,powerin)))) {
               cps[site]=strtol(sptr4+strlen(powerin),&sptr5,10);
               fprintf(stdout,"Found %s(%d)<%s>[%s],%d\n",powerin,cps[site],sptr4,sptr5,HCOVImaptoCPS[cps[site]]);
               sptr3=sptr5;
               site++;
               cps[site]=0;
               }
            }/* end sptr4==sptr3 not cps or hcovi */
         else {/* must have been a digital channel */        
// fprintf(stdout,"FOUND %ld\n",l);
            if (HFICAP || RASPCAP)  omap[site]=l;
            else {
               if (EX_TO_HF==0 || HF_TO_EX_HC==1) omap[site]=hf_to_ex[l].EX;
               else omap[site]=ex_to_hf[l].HF;/* invert back from ex to HF */
               }
            } /* end digital channel */
         }/* end TesterCh[%d] */
      else {break;}   
      }
   if (cps[1]!=0) {/* assume all channels are cps if one is! */
      *endofbasic='\0';
      fprintf(fpout,"	%s	 ",BUFFER);/* cps channels start at one so cps[j]-1 */
      if (EX_TO_HF==0 || HF_TO_EX_HC==1) {
			for (j=1;(j<site && cps[j]!=0);j++) fprintf(fpout,"TesterCh[%d] = %s%d; ",j,powerout,(HF_TO_EX_HC==1)?CPStoHCOVImapHC[cps[j]-1][1]:CPStoHCOVImap[cps[j]-1][1]);
			}
      else { /* this is for converting EX (HCOVI) back to HF (CPS), not supported for HCadapter: */
			for (j=1;(j<site && cps[j]!=0);j++) fprintf(fpout,"TesterCh[%d] = %s%d; ",j,powerout,HCOVImaptoCPS[cps[j]]);
			}
      if (bracecountclose!=2) fprintf(fpout,"}\n");
      if (bracecountclose==2) fprintf(fpout,"} }%s\n",endofnormal);
      }
   else if (site!=1 && omap[1]!=-1) {
      *endofbasic='\0';
      fprintf(fpout,"	%s	 ",BUFFER);
      if (HFICAP || RASPCAP) fprintf(fptable," [%20s]\t",name);
      for (j=1;j<site;j++) fprintf(fpout,"TesterCh[%d] = %d; ",j,omap[j]);
      for (j=1;j<site;j++) {
         if (RASPCAP) fprintf(fptable,"CAP[%d]=%4.1f;\t",j,RASP_CAP_SHORT[omap[j]]);
         else if (HFICAP) fprintf(fptable,"CAP[%d]=%4.1f;\t",j,AVECAP_TOWER  [omap[j]]);
         }
      if (bracecountclose!=2) {
//         fprintf(fptable,"HERE!");
         for (j=1;j<site;j++) {
            for (k=j+1;k<site;k++) {
            if (RASPCAP) CAPD=(fabs(RASP_CAP_SHORT[omap[j]]-RASP_CAP_SHORT[omap[k]])/RASP_CAP_SHORT[omap[k]]);
            else         CAPD=(fabs(AVECAP_TOWER  [omap[j]]-AVECAP_TOWER  [omap[k]])/AVECAP_TOWER  [omap[k]]);
//            fprintf(fptable,"[%f]",CAPD);
            if (CAPD>0.1 && (HFICAP || RASPCAP)) fprintf(fptable,"%2d-%2d diff=%3.0f%%  ",j,k,CAPD*100);
            }
            }
         fprintf(fpout,"} \n");
			if (HFICAP || RASPCAP) fprintf(fptable,"\n");
         }
      if (bracecountclose==2) {
         fprintf(fpout,"} }%s\n",endofnormal);
//         fprintf(fptable,"THERE!");
         for (j=1;j<site;j++) {
            for (k=j+1;k<site;k++) {
            if (RASPCAP) CAPD=(fabs(RASP_CAP_SHORT[omap[j]]-RASP_CAP_SHORT[omap[k]])/RASP_CAP_SHORT[omap[k]]);
            else         CAPD=(fabs(AVECAP_TOWER  [omap[j]]-AVECAP_TOWER  [omap[k]])/AVECAP_TOWER  [omap[k]]);
//            fprintf(fptable,"[%f]",CAPD);
            if (CAPD>0.1 && (HFICAP || RASPCAP)) fprintf(fptable,"%2d-%2d diff=%3.0f%%  ",j,k,CAPD*100);
            }
            }
         if (HFICAP || RASPCAP) fprintf(fptable,"\n");
         }
      }
   else {fprintf(fpout,"%s\n",BUFFER);}

   }
fclose(fpout);
fclose(fpin);
return(0);
}
