/*
To test that the Linux framebuffer is set up correctly, and that the device permissions
are correct, use the program below which opens the frame buffer and draws a gradient-
filled red square:
retrieved from:
Testing the Linux Framebuffer for Qtopia Core (qt4-x11-4.2.2)
http://cep.xor.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


void drawBlock(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int startX, int startY, int height, int width, int red, int green, int blue) {

	// finfo: bawaan
	// vinfo: bawaan
	// startY: posisi awal Y
	// startX: posisi awal X
	// height: tinggi dari block
	// width: lebar dari block
	// rgb: color rgb dari block

	  int x,y;
	  int location = 0;
	  for (y = startY; y < startY+height; y++) {
	        for (x = startX; x < startX+width; x++) {
	    	    // usleep(2);
	            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
	            if (vinfo.bits_per_pixel == 32) {
	                *(fbp + location) = blue;       // Some bluei
	                *(fbp + location + 1) = green;  // A little green
	                *(fbp + location + 2) = red;    // A lot of red
	                *(fbp + location + 3) = 0;      // No transparency
	                //location += 4;
	            } 
		    else  { //assume 16bpp
	                int b = 10;
	                int g = 10;    // A little green
	                int r = 10;    // A lot of red
	                unsigned short int t = r<<11 | g << 5 | b;
	                *((unsigned short int*)(fbp + location)) = t;
	            }
	        }
	 }
}

 
void huruf(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y, int red, int green, int blue, char h) {

    switch (h){

	case 'k' :
		 	drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 20+x,40+y, 10, 10, red, green, blue); 	 	  
		 	drawBlock(finfo, vinfo, fbp, 30+x,10+y, 10, 10, red, green, blue); 
		 	drawBlock(finfo, vinfo, fbp, 30+x,50+y, 10, 10, red, green, blue); 
		 	drawBlock(finfo, vinfo, fbp, 40+x,60+y, 10, 10, red, green, blue);
		 	drawBlock(finfo, vinfo, fbp, 40+x,0+y, 10, 10, red, green, blue); 
	 	break;

	case 'p':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 30, 10, red, green, blue);
		break;

	case 'h':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
		break;

	case 'u':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,0+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
		break;

	case 'a':
			drawBlock(finfo, vinfo, fbp, 0+x,10+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
		break;

	case 't':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 20+x,0+y, 70, 10, red, green, blue);
		break;

	case 'r':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 30, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,50+y, 20, 10, red, green, blue);
		break;

	case 'l':
			drawBlock(finfo, vinfo, fbp, 0+x,60+y, 10, 50, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
		break;

	case 'i':
			drawBlock(finfo, vinfo, fbp, x, y, 70, 10, red, green, blue);
		break;

	case 'n' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,10+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 30+x,30+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);
        break;

    case 'w' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,50+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 20+x,40+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 30+x,50+y, 10, 10, red, green, blue);
        break;
    case 'z' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 0+x,60+y, 10, 50, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,10+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 30+x,20+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 20+x,30+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 0+x,50+y, 10, 10, red, green, blue);
        break;

    case 'b' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,10+y, 20, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,40+y, 20, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
        break;

    case 'm' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,10+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 30+x,10+y, 10, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);
        break;

    case 'o':
            drawBlock(finfo, vinfo, fbp, 0+x,10+y, 50, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 40+x,10+y, 50, 10, red, green, blue); //tiang kanan
            drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
        break;

    case 'g':
	    drawBlock(finfo, vinfo, fbp, 0+x,10+y, 50, 10, red, green, blue);
	    drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 40, red, green, blue);
	    drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 40, red, green, blue);
	    drawBlock(finfo, vinfo, fbp, 40+x,30+y, 40, 10, red, green, blue);
	    drawBlock(finfo, vinfo, fbp, 30+x,30+y, 10, 20, red, green, blue);
	break;

    case 'f' :
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
            drawBlock(finfo, vinfo, fbp, 0+x,30+y, 10, 50, red, green, blue);
	break;

    case 'c':
	    drawBlock(finfo, vinfo, fbp, 0+x,10+y, 50,10, red, green, blue); //tiang kiri
            drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue); //alas bawah
            drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue); //alas atas
	break;

    case 'e':
	    drawBlock(finfo, vinfo, fbp,  0+x,10+y, 50, 10, red, green, blue); //tiang kiri
            drawBlock(finfo, vinfo, fbp, 10+x, 0+y, 10, 40, red, green, blue); //alas atas
            drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue); //alas tengah 
            drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 40, red, green, blue); //alas bawah
   	break;
    }

}

void typesentence(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y, int red, int green, int blue, char* h) {
	
	for (int i=0; i<strlen(h);i++) {

		if(h[i]=='i') 	
    			huruf(finfo, vinfo, fbp,x+(i*80),y, red, green, blue, h[i]);
		else
    			huruf(finfo, vinfo, fbp,x+(i*57),y, red, green, blue, h[i]);

	}

} 

int main()
{

    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    x = 100; y = 100;       // Where we are going to put the pixel

    int i,fr;
    // Figure out where in memory to put the pixel
    
    // Draw the BG color
    drawBlock(finfo, vinfo, fbp, 0, 0, 700, 1366, 255, 255, 255); 

    for (i = 1; i <77; i++) {
	drawBlock(finfo, vinfo, fbp, 0, 0, 700, 1366, 255, 255, 255); 
	typesentence(finfo, vinfo, fbp, 500, 600-(4*i), 30, 30, 30,"circle");
	usleep(1);		
    }
    usleep(1000);
    for (i = 78; i <154; i++) {
	drawBlock(finfo, vinfo, fbp, 0, 0, 700, 1366, 255, 255, 255); 
	typesentence(finfo, vinfo, fbp, 500, 600-(4*i), 30, 30, 30,"circle");
	usleep(1);		
    }
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}

//683x384


















































// disini bisa dipake buat ngeplay, nanti buat animasi
    	// bisa pakai fungsi buat ubah posisi

    	// SEBELUM UBAH huruf, dilihat dulu semua hurufnya

    	// ukuran frame huruf belum sama
    	// kalo mau ganti ukuran huruf, harus diganti
    	// satu per satu parameternya

    	// for (y = 84; y < 674; y++){
	    //     for (x = 83; x < 1273; x++) {
	    //     	coba.r[x][y]=i;
	    //     	coba.g[x][y]=i;
	    //     	coba.b[x][y]=i;
	    //     	}
	    //     }

	    /* huruf A
    	drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 200, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 300, 50, 50, 50, 100, 100);
	 	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
		*/
		
	 	/* huruf I
    	drawBlock(finfo, vinfo, fbp, 125, 200, 25, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 125, 375, 25, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 200, 25, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 375, 25, 50, 50, 100, 100);
	 	*/

		/* huruf U
    	drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 350, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
    	*/
		
		/* huruf O
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 200, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 350, 50, 50, 50, 100, 100);
	 	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
		*/

    	/* huruf L
    	drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 350, 50, 75, 50, 100, 100);
		*/

    	/* huruf H
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 275, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
    	*/

    	/* huruf T
    	drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 100, 200, 50, 150, 50, 100, 100);
    	*/

    	/* huruf M (masih cacat)
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 185, 200, 200, 35, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 200, 200, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 100, 200, 50, 200, 50, 100, 100);
		*/

		/* huruf G
		drawBlock(finfo, vinfo, fbp, 100, 200, 50, 200, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 100, 400, 50, 200, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 300, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 250, 300, 100, 50, 50, 100, 100);
    	*/

    	/* huruf K
		drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 300, 50, 100, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 250, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 300, 200, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 350, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 300, 400, 50, 50, 50, 100, 100);
        */     	

		/* huruf R
		drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 200, 50, 100, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 300, 50, 150, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 250, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 400, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 200, 350, 50, 50, 50, 100, 100);
		*/	
