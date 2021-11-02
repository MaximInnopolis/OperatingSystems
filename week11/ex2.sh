sudo chmod 777 lofsdisk
sudo touch lofsdisk/file1
sudo chmod 777 lofsdisk/file1
sudo touch lofsdisk/file2
sudo chmod 777 lofsdisk/file2
echo "Maxim" > lofsdisk/file1
echo "Latypov" > lofsdisk/file2
gcc -o ex2.out ex2.c
sudo mkdir lofsdisk/bin
sudo cp -R /bin/bash lofsdisk/bin
sudo cp -R /bin/cat lofsdisk/bin
sudo cp -R /bin/echo lofsdisk/bin
sudo cp -R /bin/ls lofsdisk/bin
sudo mkdir lofsdisk/lib
sudo mkdir lofsdisk/lib64
sudo cp -R /lib lofsdisk/lib
sudo cp -R /lib64 lofsdisk/lib64
cd lofsdisk
gcc -o ex2.out ../ex2.c
echo "Сhroot:" >> ../ex2.txt
sudo chroot . /bin/ls
echo "Without chroot:" >> ../ex2.txt
./ex2.out >> ../ex2.txt