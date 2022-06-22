class enemyRect {
    constructor() {
        this.x = random(0+20, width-20);
        this.y = random(0+30, 150);
        this.d = 40;
        this.check = 1;
        //this.velocity = 0.2
        this.rand = int(random(2));
        if(this.rand == 0) { 
            this.velocityX = random(0,1); 
        } 
        else if(this.rand == 1) { 
            this.velocityX = -random(0,1); 
        } 
        this.velocityY = random(0,1);
        this.accel = 0.01;
        this.bh = gImages_b;
        this.rh = gImages_r;
        this.yh = gImages_y;
        this.gh = gImages_g;
        this.bb = gImages_bomb;
        this.land = int(random(1, 6));
        switch(this.land) {
            case 1 :
                this.img = this.bh;
                break;
            case 2 :
                this.img = this.rh;
                break;
            case 3 :
                this.img = this.yh;
                break;
            case 4 :
                this.img = this.gh;
                break;
            case 5 :
                this.img = this.bb;
                break;
        }
    }

    display() {
       push();
       imageMode(CENTER);
       image(this.img, this.x, this.y, this.d, this.d);
       pop(); 
    }

    move() {
        this.velocityY += this.accel;
        this.x += this.velocityX;
        this.y += this.velocityY;    
        if(this.x > width-(this.d/2) || this.x < 0+(this.d/2))
        {
            this.velocityX *= -1;
        }
    }
        

    reset() {
        this.x = random(0+20, width-20);
        this.y = 40;
        this.d = 35;
        //this.velocity = 0.5
        this.rand = int(random(2));
        if(this.rand == 0) { 
            this.velocityX = random(0,1); 
        } 
        else if(this.rand == 1) { 
            this.velocityX = -random(0,1); 
        } 
        this.velocityY = random(0,1);
        this.accel = 0.01;
        this.bh = gImages_b;
        this.rh = gImages_r;
        this.yh = gImages_y;
        this.gh = gImages_g;
        this.bb = gImages_bomb;
        this.land = int(random(1, 6));
        switch(this.land) {
            case 1 :
                this.img = this.bh;
                break;
            case 2 :
                this.img = this.rh;
                break;
            case 3 :
                this.img = this.yh;
                break;
            case 4 :
                this.img = this.gh;
                break;
            case 5 :
                this.img = this.bb;
                break;
        }
    }
}