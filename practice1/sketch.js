let rectNormal = [];
let normalNum = 1;
let rectEnemy = [];
let enemyNum = 15;
let button;
let button2;

let mode = 0;
let mode1 = 0;
let SCORE = 0;


// const BLUEHEART = 'blueheart';
// const GREENHEART = 'greenheart';
// const REDHEART = 'redheart';
// const YELLOWHEART = 'yellowheart';

let gImages_b, gImages_g, gImages_r, gImages_y, gImages_bomb, gImages_gold, gImages_play;
let gImages_backGr;
let gImages = {};

let method;


let timeValue =  30;
let a;

// let overBox = false; // 마우스 위치 체크
// let locked = false;
// let xOffset = 0.0;
// let yOffset = 0.0;

function preload() {
  gImages_b = loadImage( 'blueheart.png' );
  gImages_g = loadImage( 'greenheart.png' );
  gImages_r = loadImage( 'redheart.png' );
  gImages_y = loadImage( 'yellowheart.png' );
  gImages_bomb = loadImage( 'bomb.png' );
  gImages_space = loadImage( 'space.jpg' );
  gImages_back = loadImage( 'drawback2.png' );
  gImages_play = loadImage( 'howtoplay.jpg' );
  gImages_backGr = loadImage( 'backgroundpho.png' );

  coinSound = loadSound( 'coin.wav' );
  bombSound = loadSound( 'bomb.mp3' );
  warpSound = loadSound( 'warp.wav' );

  retroFont = loadFont( 'Sam3KRFont.ttf' );
  //method = loadStrings('Howtoplay.txt');
}

function textPrint() {
  push();
  fill('#CA82FB');

  rect(0,0,width,30);
  textFont(retroFont);
  fill(0);
  textSize(15);
  //textAlign(CENTER);
  text("SCORE : " + SCORE, 170, 20);
  pop();
}


function setup() {
  // if(SCORE = 30) {
  //   updateMode();
  // }
  createCanvas(400, 600);
  //background(200);

  //clickSound.play();
  button = createButton("Game Start");
  button.size(150, 50);
  button.position(width/2 - 75, height/2 - 50);
  button.mousePressed(updateMode);

  button2 = createButton("How to play");
  button2.size(150, 50);
  button2.position(width/2 - 75, height/2 + 25);
  button2.mousePressed(updateMode2);
  // button2.mousePressed(updateMode);
  
  for(let i = 0; i < normalNum; i++) {
    rectNormal[i] = new normalRect();
  }

  for(let i = 0; i < enemyNum; i++) {
    rectEnemy[i] = new enemyRect();
  }

  // fill('D8A6FB');
  // rect(width/2, height-30, width, 60);

  //createCanvas(400, 100);
  //textAlign(CENTER);
  setInterval(timeIt, 1000); //

  
}


function draw() {
  
  if(mode == 0) { // mode 스테이지 구분
    background("#D1F1F7");
    //imageMode(CENTER);
    image(gImages_backGr, 0, 0, width, height);
    
  }
  if(mode == 1) {

    //gameOver();
    removeElements();
    background(255);
    image(gImages_space, 0, 0, width, height);
    endOfGame();
    //changeImg();
    textPrint();
    Timer();

    for(let i = 0; i < enemyNum; i++) {
      rectEnemy[i].display();
      rectEnemy[i].move();

    }

    push();
    textFont(retroFont);
    textSize(15);
    //textAlign(CORNER);
    text("Goal = 10", 25, 21);
    pop();

    fill(255, 255, 0, 200);
    noStroke();
    rect(0, 480, width, 120);
    
    for(let i = 0; i < normalNum; i++) {
      //a = map(SCORE, 0, 10, 0, 200);
      rectNormal[i].display();
    }

    gameOver();

    // for(let i = 0; i < normalNum; i++) {
    //   rectNormal[i].display();
    //   for(let j = 0; j < enemyNum; j++) {
    //     if(rectEnemy[j].c = color(255, 0, 0)) {
    //       a = map(SCORE, 0, 10, 0, 200);
    //       a = rectNormal[i].arg1;
    //     }
    //   }
    // }

    

    if(SCORE >= 10) {
      fill(0);
      rect(0, 0, width, height);
      button = createButton("Next Mode");
      //button.textSize(30);
      button.size(200, 50);
      button.position(width/2-100, height/2-25);
      button.mousePressed(updateMode);
      //SCORE = 0;
    }
   
  }


  if(mode == 2) {
    removeElements();
    background(0);
    image(gImages_space, 0, 0, width, height);
    //SCORE = 0
    endOfGame();
    textPrint();
    Timer();
    //timeIt();
    
    for(let i = 0; i < enemyNum; i++) {
      rectEnemy[i].display();
      rectEnemy[i].move();
    }

    push();
    textFont(retroFont);
    textSize(15);
    //textAlign(CORNER);
    text("Goal = 15", 25, 21);
    pop();

    fill(255, 255, 0, 200);
    noStroke();
    rect(0, 480, width, 120);
    
    for(let i = 0; i < normalNum; i++) {
      rectNormal[i].display();
    }

    gameOver();

    if(SCORE >= 15) {
      fill(0);
      rect(0, 0, width, height);
      button = createButton("Next Mode");
      //button.textSize(30);
      button.size(200, 50);
      button.position(width/2-100, height/2-25);
      button.mousePressed(updateMode);
      //SCORE = 0;
    }
  }

  if(mode == 3) {
    removeElements();
    background(0);
    image(gImages_space, 0, 0, width, height);
    //SCORE = 0
    endOfGame();
    textPrint();
    Timer();
    //timeIt();
    
    for(let i = 0; i < enemyNum; i++) {
      rectEnemy[i].display();
      rectEnemy[i].move();
    }

    push();
    textFont(retroFont);
    textSize(15);
    //textAlign(CORNER);
    text("Goal = 20", 25, 21);
    pop();

    fill(255, 255, 0, 200);
    noStroke();
    rect(0, 480, width, 120);
    
    for(let i = 0; i < normalNum; i++) {
      rectNormal[i].display();
    }
    
    gameOver();

    // if(keyIsPressed && keyCode == ENTER) {
    //   mode = mode - 2;
    // }


    if(SCORE >= 20) {
      push();
      fill(0);
      rect(0, 0, width, height);
      fill(255, 255, 0);
      textFont(retroFont);
      textSize(20);
      textAlign(CENTER);
      text("you can escape from this game", width/2, 550);
      button = createButton("Go to Start Screen");
      //button.textSize(30);
      button.size(200, 50);
      button.position(width/2-100, height/2-25);
      button.mousePressed(finish);
      //SCORE = 0;
      pop();
      
    }

  }
  
  // if(mode == 4) {
  //   removeElements();
  //   background(0);

  // }


  if(mode1 == 1) {
    removeElements();
    background(100);
    push();
    fill(0);
    image(gImages_play, 0, 0, width, height);

    // textAlign(CENTER);
    // textSize(15);
    // text(method, 10, 10, width-10, height);
    if(keyIsPressed && keyCode == BACKSPACE) {
      mode1 = mode;
      mode = mode + 1;
      timeValue = 30;
    }
    fill("#9BF178");
    textAlign(CENTER);
    push();
    textFont(retroFont);
    textSize(25);
    text('If you want to start game, \n\nPlease press backspace.', 10, 500, width-10, height)
    pop();
  }

}

function updateMode() {
  mode = mode + 1;
  if(mode == 2 && SCORE == 15) {
    mode = mode + 2;
  }
  SCORE = 0;
  timeValue = 30;
  for(let i = 0; i < normalNum; i++) {
    rectNormal[i].reset();
  }
  modeCheck = true;
}

function updateMode2() {
  mode1 = mode1 + 1;
}

function mousePressed() {
  for(let j = 0; j < normalNum; j++) {
    for(let i = 0; i < enemyNum; i++) {
      let dis = 100;
      dis = dist(mouseX, mouseY, rectEnemy[i].x, rectEnemy[i].y);
      if(dis < rectEnemy[i].d*2/3) {
        if(rectNormal[j].img == rectEnemy[i].img) {
          coinSound.play();
          SCORE = SCORE + 1;
        }
        if(rectEnemy[i].img == rectEnemy[i].bb) {
          bombSound.play();
          SCORE = 0;
        }
        if(rectNormal[j].img != rectEnemy[i].img) {
          if(SCORE > 0) {
            warpSound.play();
            SCORE = SCORE - 1;
          }
        }
        rectEnemy[i].reset();
      }
      // else if(rectNormal[j].c != rectEnemy[i].c) {
      //   SCORE--;
      // }
    }
  }
}


function endOfGame() {
  for(let i = 0; i < enemyNum; i++) {
    if(rectEnemy[i].y > height - (120+rectEnemy[i].d/2)) {
      rectEnemy[i].reset();
    }
  }
}

function gameOver() {
  if(timeValue == 0) {
    if(mode == 1) {
    push();
    //removeElements();
    background(0);
    textFont(retroFont);
    fill(227, 101, 91);
    textSize(50);
    textAlign(CENTER);
    text("Game over", width/2, height/2);
    pop();
    }
    else if(mode == 2) {
      push();
      //removeElements();
      background(0);
      textFont(retroFont);
      fill(227, 101, 91);
      textSize(50);
      textAlign(CENTER);
      text("Game over", width/2, height/2);
      pop();
    }
    else {
      push();
      //removeElements();
      background(0);
      if(keyIsPressed && keyCode == ENTER) {
        mode = mode - 2;
        timeValue = 30;
        SCORE = 0;
      }
      textFont(retroFont);
      fill(255, 0, 0);
      textSize(40);
      textAlign(CENTER);
      text("Please press \nEnter After 3 second", width/2, height/2);
      pop();
    }
  }
}

function finish() {
  mode = mode - 3;
  removeElements();
  button = createButton("Game Start");
  button.size(150, 50);
  button.position(width/2 - 75, height/2 - 50);
  button.mousePressed(updateMode);

  button2 = createButton("How to play");
  button2.size(150, 50);
  button2.position(width/2 - 75, height/2 + 25);
  button2.mousePressed(updateMode2);
}

function Timer() {
  push();
  if(timeValue >= 10) {
    textFont(retroFont);
    fill('#FF003A');
    textSize(15);
    text("0:" + timeValue, 350, 20);
  }
  if(timeValue < 10) {
    textFont(retroFont);
    fill('#FF003A');
    text("0:0" + timeValue, 350, 20);
  }
  pop();
}

function timeIt() {
  if(timeValue > 0) {
    timeValue = timeValue-1
  }
}

// function changeImg() {
//   for(let j = 0; j < normalNum; j++) {
//     if(keyPressed && keyCode == ENTER) {
//       rectNormal[j].reset();
//     }
//   }
// }

// for(let i = 0; i < normalNum; i++) {
//   if (overBox) { // 마우스가 노말 사각형 안에 있으면
//     locked = true;
//     fill(255, 255, 255);
//   } 
//   else {
//     locked = false; // 마우스가 노말 사각형 밖에 있으면 locked는 false가 된다.
//   }

//   print(xOffset, yOffset);
//   xOffset = mouseX - rectNormal[i].x; // mouseX와 노말사각형 사이의 거리 = xOffset
//   yOffset = mouseY - rectNormal[i].y; // mouseY와 노말사각형 사이의 거리 = yOffset
// }

// if(mousePressed && this.img == gImages[ REDHEART ]) {

// }


