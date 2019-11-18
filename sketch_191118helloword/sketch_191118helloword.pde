void setup(){//setforbackground
  
  size(180,180);//size
}
void draw(){
  background(mouseX,mouseY,100);//color(red,green,blue)
  if(keyPressed){//scanf
    fill(95);//fillcolor
  }else{
    fill(240);
  }
  ellipse(mouseX,mouseY,10,10);//(site,size)
}
