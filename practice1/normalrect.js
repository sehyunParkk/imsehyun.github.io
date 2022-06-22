class normalRect {
    constructor() {
        
        this.d = 70;
        this.x1 = width/2;
        // this.x2 = 160 - this.d/2;
        // this.x3 = 240 - this.d/2;
        // this.x4 = 320 - this.d/2;
        this.y = 540;
        this.bh = gImages_b;
        this.rh = gImages_r;
        this.yh = gImages_y;
        this.gh = gImages_g;
        this.land = int(random(1, 5));
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
        }
        //this.current = this.img;
        this.alpha = 200;
        //this.alpha = map(SCORE, 0, 10, 100, 0);
    }

    display() {
        push();
        imageMode(CENTER);
        //print(fill());
        image(this.img, this.x1, this.y, this.d, this.d);
        pop();
    }

    reset() {
        this.d = 70;
        this.x1 = width/2;
        // this.x2 = 160 - this.d/2;
        // this.x3 = 240 - this.d/2;
        // this.x4 = 320 - this.d/2;
        this.y = 540;
        this.bh = gImages_b;
        this.rh = gImages_r;
        this.yh = gImages_y;
        this.gh = gImages_g;
        this.land = int(random(1, 5));
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
        }
        
    }

   
}
