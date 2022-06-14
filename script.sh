cd bin

time ./bedroom -w 1024 -h 1024 -s 512 -d 10 -t 31 -i path

time ./bmps -w 1200 -h 1000 -s 512 -d 10 -t 31 -i path -r 0.15 -o "../image/bmps_015.ppm"
time ./bmps -w 1200 -h 1000 -s 512 -d 10 -t 31 -i path -r 0.35 -o "../image/bmps_035.ppm"
time ./bmps -w 1200 -h 1000 -s 512 -d 10 -t 31 -i path -r 0.55 -o "../image/bmps_055.ppm"
time ./bmps -w 1200 -h 1000 -s 512 -d 10 -t 31 -i path -r 0.75 -o "../image/bmps_075.ppm"

time ./desk -w 1120 -h 630 -s 512 -d 10 -t 31 -i path

time ./Higokumaru -w 1920 -h 1080 -s 512 -d 10 -t 31 -i path

time ./mis -w 1024 -h 1024 -s 64 -d 10 -t 31 -i light -o "../image/mis_light.ppm"
time ./mis -w 1024 -h 1024 -s 64 -d 10 -t 31 -i brdf -o "../image/mis_brdf.ppm"
time ./mis -w 1024 -h 1024 -s 64 -d 10 -t 31 -i mis -o "../image/mis_mis.ppm"

time ./poke -w 1024 -h 1024 -s 512 -d 10 -t 31 -i path

time ./street -w 1024 -h 1024 -s 512 -d 10 -t 31 -i path

time ./teapot -w 1120 -h 630 -s 512 -d 10 -t 31 -i path
