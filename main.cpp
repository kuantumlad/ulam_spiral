////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/*
Ulam's Spiral
Author @B.Clary

Ulam's spiral is a graphical representation
of the prime numbers. This is created by starting
with 1 in the center of a grid and moving
left by one unit to 2, then up for 3, left for 4, etc, in 
a counter clockwiser pattern.
   5  4  3
   6  1  2
   7  8  9 ... etc

The prime numbers are highlighted in red in the 
produced image, these numbers sit in unique patterns
along the diagonal, and horizontal lines. 


Purpose:
1)Illustrate Ulam's spiral using C++
2) Learn and use dynamic programming to create the objects for
   storing SFML objects.
*/
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main(int argc, const char* input[]){


  std::cout << " Starting Ulam's Spiral program! " << std::endl;
  sf::Font font;
  if ( !font.loadFromFile("arial.ttf") ){
    std::cout << " error loading font file. " << std::endl;
  }
  
  int windowX = 1500;
  int windowY = 1500;
  
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); 
  int globalX = 0.0;
  int globalY = 0.0;
  sf::Vector2i window_pos(globalX, globalY);

  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"NUMBERS" );
  window.setPosition(window_pos);

  //min and max block size
  int max_block_size = 150;
  int block_size = 3;

  //counters and shifters for position
  int current_number = 1;
  int shift = 0;  
  int number = 0;
  int y_txt_shift = 0;
  int char_size = 10;
  

  const int ulam_gridX=max_block_size;
  const int ulam_gridY=max_block_size;
  
  //traditional way to create 2d array
  sf::Text ulam_grid[20][20];

  //The fat and slow method
  //testing dynamic allocation of memory using arrays  
  sf::CircleShape **ulam_grid_circles = new sf::CircleShape*[ulam_gridY];
  for( int i = 0; i < ulam_gridY; i++ ){
    ulam_grid_circles[i] = new sf::CircleShape[ulam_gridX];
  }

  //The thin and fast method
  //Dynamic allocation using one dynamically allocated array of size ulam_gridX*ulam_gridY  
  sf::CircleShape *ulam_grid_circles_lte = new sf::CircleShape[ulam_gridX*ulam_gridY];
  
  int globX_index = max_block_size/2 - 1;
  int globY_index = max_block_size/2 - 1;

  int grid_space_x = windowX/max_block_size;
  int grid_space_y = windowY/max_block_size;
  
  for( int i = 0; i < max_block_size; i++){
    double x_pos = i * grid_space_x;      
    for( int j = 0; j < max_block_size; j++ ){
      double y_pos = j*grid_space_y;
      sf::CircleShape circle;
      circle.setRadius(5);
      circle.setFillColor(sf::Color::White);
      circle.setPosition(x_pos,y_pos);

      //fill the fat and slow object
      ulam_grid_circles[i][j]=circle;

      //fill the thin and fast object
      ulam_grid_circles_lte[i*ulam_gridY + j]=circle;
    }
  }
  
  //block is defined as the basic unit
  //a block consists of completing the sequence:
  //right -> up -> left -> down 
  while( block_size < max_block_size ){
    int seq=0;

    //execute sequence elements
    while( seq < 4 ){
      if( seq == 0 ){ //go right
	int count_seq1=0;
	//account for starting position
 	if( current_number == 1 ) shift = 2;
	else if ( current_number != 1 ) shift = 1;

 	if( block_size > 3 ) shift = 2;

	//number of elements in sequence step
	while( count_seq1 < block_size - shift ){
	  current_number++;

	  //determine if number is prime
	  int is_div_counter = 0;
	  for( int i = 1; i <=current_number; i++ ){
	    if( current_number%i == 0 ){
	      is_div_counter++;
	    }
	  }
	  
	  //shift in x for right sequence
	  int x_index_seq1 = globX_index +1;
	  int y_index_seq1 = globY_index;
	  //do stuff here
	  
	  //color prime numbers red
	  if( is_div_counter == 2 ){
	    ulam_grid_circles[x_index_seq1][y_index_seq1].setFillColor(sf::Color::Red); 	  
	    ulam_grid_circles_lte[x_index_seq1*ulam_gridY + y_index_seq1].setFillColor(sf::Color::Red); 	  
	  }
	  else{
	    //color the text 
	    //euler_grid[x_index_seq1][y_index_seq1].setFillColor(sf::Color::White);
	  }

	  //set current index to global index for next step in sequence
	  globX_index = x_index_seq1;
	  globY_index = y_index_seq1;	 	  
	  count_seq1++;
	}
      }
      if( seq == 1 ){ //go up
	int count_seq2=0;	
	while( count_seq2 < block_size - shift ){
	  current_number++;

	  int is_div_counter = 0;
	  for( int i = 1; i <= current_number; i++ ){
	    if( current_number%i == 0 ){
	      is_div_counter++;
	    }
	  }	  

	  //draw 
	  int x_index_seq2 = globX_index;
	  int y_index_seq2 = globY_index-1;
	  //do stuff here

	  //euler_grid[x_index_seq2][y_index_seq2].setString(std::to_string(current_number));
	  if( is_div_counter == 2 ){
	    ulam_grid_circles[x_index_seq2][y_index_seq2].setFillColor(sf::Color::Red); 
	    ulam_grid_circles_lte[x_index_seq2*ulam_gridY + y_index_seq2].setFillColor(sf::Color::Red); 	  
	    //euler_grid[x_index_seq2][y_index_seq2].setFillColor(sf::Color::Red);
	  }
	  else{
	    //euler_grid[x_index_seq2][y_index_seq2].setFillColor(sf::Color::White);
	  }

	  globX_index = x_index_seq2;
	  globY_index = y_index_seq2;
	  	  
	  count_seq2++;
	}
      }
      if( seq == 2 ){ //go left
	int count_seq3=0;	
	while( count_seq3 < block_size - 1 ){
	  current_number++;

	  int is_div_counter = 0;
	  for( int i = 1; i <= current_number; i++ ){
	    if( current_number%i == 0 ){
	      is_div_counter++;
	    }
	  }	  

	  int x_index_seq3 = globX_index - 1;
	  int y_index_seq3 = globY_index;
	  //do stuff here
	  //ulam_grid[x_index_seq3][y_index_seq3].setString(std::to_string(current_number));

	  if( is_div_counter == 2 ){
	    ulam_grid_circles[x_index_seq3][y_index_seq3].setFillColor(sf::Color::Red);
	    ulam_grid_circles_lte[x_index_seq3*ulam_gridY + y_index_seq3].setFillColor(sf::Color::Red); 	  
	    //euler_grid[x_index_seq3][y_index_seq3].setFillColor(sf::Color::Red);
	  }
	  else{
	    //euler_grid[x_index_seq3][y_index_seq3].setFillColor(sf::Color::White);
	  }

	  globX_index = x_index_seq3;
	  globY_index = y_index_seq3;

	  count_seq3++;
	}
      }
      if( seq == 3 ){ //go down
	int count_seq4=0;	
	while( count_seq4 < block_size - 1 ){
	  current_number++;
	  
	  int is_div_counter = 0;
	  for( int i = 1; i <= current_number; i++ ){
	    if( current_number%i == 0 ){
	      is_div_counter++;
	    }
	  }	  

	  int x_index_seq4 = globX_index;
	  int y_index_seq4 = globY_index+1;
	  //do stuff here
 	  //ulam_grid[x_index_seq4][y_index_seq4].setString(std::to_string(current_number));
	  if( is_div_counter == 2 ){
	    ulam_grid_circles[x_index_seq4][y_index_seq4].setFillColor(sf::Color::Red);
	    ulam_grid_circles_lte[x_index_seq4*ulam_gridY + y_index_seq4].setFillColor(sf::Color::Red); 	  
	    //ulam_grid[x_index_seq4][y_index_seq4].setFillColor(sf::Color::Red);
	  }
	  else{
	    //ulam_grid[x_index_seq4][y_index_seq4].setFillColor(sf::Color::White);
	  }
	  globX_index = x_index_seq4;
	  globY_index = y_index_seq4;
	  
	  count_seq4++;
	}
      }      
      seq++;     
    }
    y_txt_shift++;
    block_size=block_size + 2;
    number = current_number;    
  }


  
  while( window.isOpen() ){
    sf::Event event;
    while( window.pollEvent(event) ){
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
      }
    }

    window.clear(sf::Color::Black);

    for(int i = 0; i < max_block_size; i++ ){
      for(int j = 0; j < max_block_size; j++ ){
	//window.draw(ulam_grid_circles[i][j]);
	window.draw(ulam_grid_circles_lte[i*ulam_gridY + j]);

      }
    }
    window.display();
  }
 
  //clean up allocation of memory for 2D matrix
  for(int i =0; i < ulam_gridY; i++ ){
    delete [] ulam_grid_circles[i];
  }
  delete [] ulam_grid_circles;

  //clean up allocation of memory for array of size ulam_gridX*ulam_gridY
  delete [] ulam_grid_circles_lte;
 
  return 0; 
  
}
