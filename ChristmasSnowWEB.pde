/* @pjs preload="pics/background.jpg"; */
/* @pjs preload="pics/background2.jpg"; */
/* @pjs preload="pics/background3.jpg"; */
/* @pjs preload="pics/background4.jpg"; */
/* @pjs preload="pics/Frost.png"; */


flakeGroup front;
flakeGroup middle;
flakeGroup back;
ArrayList<PImage> backgrounds;
PImage background1, background2, background3, background4, frost;
int bg = 3;

void setup() {
  size(640, 480);
  noStroke();
  front = new flakeGroup(0);
  middle = new flakeGroup(1);
  back = new flakeGroup(2);
  background1 = loadImage("pics/background.jpg");
  background2 = loadImage("pics/background2.jpg");
  background3 = loadImage("pics/background3.jpg");
  background4 = loadImage("pics/background4.jpg");
  frost = loadImage("pics/Frost.png");
  backgrounds = new ArrayList<PImage>();
  backgrounds.add(background1);
  backgrounds.add(background2);
  backgrounds.add(background3);
  backgrounds.add(background4);
}

void draw() {
  image(backgrounds.get(bg), 0, 0);
  front.run();
  middle.run();
  back.run();
  image(frost, 0, 0);
}

void keyPressed() {
  if(key == '1') {
   bg = 0; 
  }
  else if(key == '2') {
   bg = 1; 
  }
  else if(key == '3') {
   bg = 2; 
  }
  else if(key == '4') {
   bg = 3; 
  }
}

class flakeGroup {
 ArrayList<flake> flakes;
 int type;
 
 flakeGroup() {
   flakes = new ArrayList<flake>();
   type = 0;
 }
 
 flakeGroup(int t) {
   flakes = new ArrayList<flake>();
   type = t;
 }
 
 void removeFlake(int i) {
   flakes.remove(i);
 }
 
 void run() {
   flakes.add(new flake(type));
   for (int i = 0; i < flakes.size(); i++) {
    flakes.get(i).run();
    if (!flakes.get(i).active) {
     flakes.remove(i);
     i--;
    }
   }
 }
 
}

class flake {
  PVector location;
  float vx, vy;
  int type;
  float level;
  boolean active;
  
  flake() {
    location = new PVector(random(width), 0); 
    vx = 0;
    vy = 0;
    type = 0;
    level = 1;
    active = true;
  }
  
  flake(int t) {
    location = new PVector(random(width), 0); 
    vx = 0;
    vy = 0;
    type = t;
    level = 1.0 / (t + 1);
    active = true;
  }
  
  float jitter() {
   return random(3) - 1.5; 
  }
  
  void run() {
    update();
    display();
  }
  
  void update() {
   //general moving
    location.x += (vx * level) + jitter();
    if (abs(vx) > 0) {
     if (vx > 0) {
      vx -= (1.0 / level); 
     }
     else if (vx < 0) {
      vx += (1.0 / level); 
     }
    }
    location.y += 1 + (vy * level) + jitter();
    if (abs(vy) > 0) {
     if (vy > 0) {
      vy -= (1.0 / level); 
     }
     else if (vy < 0) {
      vy += (1.0 / level); 
     }
    }
    
    if (mousePressed && (mouseButton == LEFT)) { //on click
      float dx = mouseX - location.x;
      float dy = mouseY - location.y;
      if ((abs(dx) * abs(dx)) + (abs(dy) * abs(dy)) <= (150 * 150 * level)) {
       if (dx > 0) { //flake left of mouse
         location.x -= 15 * level;
         vx -= sqrt((dx * dx) / 150) * level;
       }
       else if(dx < 0) { //flake right of mouse
         location.x += 15 * level;
         vx += sqrt((dx * dx) / 150) * level;
       }
       if (dy > 0) { //flake aobve of mouse
         location.y -= 15 * level;
         vy -= sqrt((dy * dy) / 150) * level;
       }
       else if(dy < 0) { //flake below of mouse
         location.y += 15 * level;
         vy += sqrt((dy * dy) / 150) * level;
       }
      }
    }
    
    if (location.y > height) { //flake no longer visible 
     active = false; 
    }
  }
  
  void display() { 
    if (type == 0) {
      fill(255, 255, 255);
      ellipse(location.x, location.y, 4, 4);
    }
    else if (type == 1) {
      fill(223, 223, 223);
      ellipse(location.x, location.y, 3, 3);
    }
    else {
      fill(191, 191, 191);
      ellipse(location.x, location.y, 2, 2);
    }
  }
}
