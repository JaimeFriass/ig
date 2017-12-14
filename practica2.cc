//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include<time.h>
#include <objetos.h>
#include "CImg.h"
using namespace cimg_library;

// tamaño de los ejes
const int AXIS_SIZE = 5000;
char teclaPulsada;

int modo = 4;
int figura = 0;
int material = 0;
int modelo = 0;

string archivoTex = "./meninas.jpg";

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// Objetos

_puntos3D puntos(); 
_triangulos3D triangulo();
//_revolucion revo();

_piramide lapira(5,7);
_cubo elcubo(5);
_tablero tablo;
//_ply objeto("./ply_files/beethoven.ply",1);
//_revolucion_inv revo(vertices, 6, true, true);

_lego legamen;

int alfa = 0;


// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width, Window_height, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x = 200, UI_window_pos_y = 50, UI_window_width = 1200, UI_window_height = 1200;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -Observer_distance);
	glRotatef(Observer_angle_x, 1, 0, 0);
	glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1, 0, 0);
	glVertex3f(-AXIS_SIZE, 0, 0);
	glVertex3f(AXIS_SIZE, 0, 0);
	// eje Y, color verde
	glColor3f(0, 1, 0);
	glVertex3f(0, -AXIS_SIZE, 0);
	glVertex3f(0, AXIS_SIZE, 0);
	// eje Z, color azul
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -AXIS_SIZE);
	glVertex3f(0, 0, AXIS_SIZE);
	glEnd();
}
void luces() {

	/*
	GLfloat light_position[4] = {0,1,1,0};

	glDisable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	*/
	GLfloat light_position[4]={0,1,1,0},
			light1_position[4]={0,1,1,1},
			light1_ambient[4]={0.1,0.1,0.1,1},
			light1_intensity[4]= {1,0.1,0.0,5};


	glLightfv(GL_LIGHT1, GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,light1_intensity);
	glLightfv(GL_LIGHT1, GL_SPECULAR,light1_intensity);
	
	glPushMatrix();
		glRotatef(alfa,1,0,0); // El primer valor seria alfa	
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
}
//**********************************************************************
// Funcion para cargar la textura
//***********************************************************************

GLuint textura_id;

void prepara_textura(void){
  vector<unsigned char> data;
  CImg<unsigned char> logo;

  logo.load(archivoTex.c_str());

  // empaquetamos bien los datos
  for (long y = 0; y < logo.height(); y++){
    for (long x = 0; x < logo.width(); x++){
      unsigned char *r = logo.data(x, y, 0, 0);
      unsigned char *g = logo.data(x, y, 0, 1);
      unsigned char *b = logo.data(x, y, 0, 2);
      data.push_back(*r);
      data.push_back(*g);
      data.push_back(*b);
    }
  }

  glGenTextures(1, &textura_id);
  glBindTexture(GL_TEXTURE_2D, textura_id);

  glActiveTexture(GL_TEXTURE0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // TRASFIERE LOS DATOS A GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

string materialToString(const int &material) {
	string mat;
	switch (material) {
		case 0: mat="BRASS"; break;
		case 1: mat="BRONZE"; break;
		case 2: mat="POLISHED BRONZE"; break;
		case 3: mat="CHROME"; break;
		case 4: mat="COPPER"; break;
		case 5: mat="POLISHED COPPER"; break;
		case 6: mat="GOLD"; break;
		case 7: mat="POLISHED GOLD"; break;
		case 8: mat="SILVER"; break;
		case 9: mat="POLISHED SILVER"; break;
		case 10: mat="EMERALD"; break;
		case 11: mat="JADE"; break;
		case 12: mat="OBSIDIAN"; break;
		case 13: mat="PEARL"; break;
		case 14: mat="RUBY"; break;
		case 15: mat="TURQUOISE"; break;
		case 16: mat="BLACK PLASTIC"; break;
		case 17: mat="BLACK RUBBER"; break; 
		default: mat="INDEFINIDO"; break;
	}
	return mat;
}

string figuraToString(const int &figura) {
	string fig;
	switch (figura) {
		case 1: fig="PIRAMIDE"; break;
		case 2: fig="CUBO"; break;
		case 3: fig="PLY"; break;
		case 4: fig="REVOLUCION"; break;
		case 5: fig="LEGO"; break;
		case 6: fig="TABLERO"; break;
		default: fig="INDEFINIDO"; break;
	}
	return fig;
}

string modoToString(const int &modo) {
	string mod;
	switch (modo) {
		case 1: mod="PUNTOS"; break;
		case 2: mod="ARISTAS"; break;
		case 3: mod="SOLIDO"; break;
		case 4: mod="AJEDREZ"; break;
		case 5: mod="ILUMINACION PLANA"; break;
		case 6: mod="ILUMINACION SUAVE"; break;
		case 7: mod="TEXTURA"; break;
		default: mod="INDEFINIDO"; break;
	}
	return mod;
}
//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
		string local;
		if (figura == 3) {
			switch(modelo){
				case 0: local="./ply_files/beethoven.ply"; break;
				case 1: local="./ply_files/ant.ply"; break;
				case 2: local="./ply_files/big_dodge.ply"; break;
				case 3: local="./ply_files/16.ply"; break;
				case 4: local="./ply_files/london.ply"; break;
				case 5: local="./ply_files/vespa.ply"; break;
				case 6: local="./ply_files/warthog.ply"; break;
				case 7: local="./ply_files/laptop.ply"; break;
				default: local="./ply_files/beethoven.ply"; break;
			}
		}
		_ply objeto(local,1);

	
	cout << "\n\n\n\n\n\n\n|*|------------- PRACTICA 4 - ILUMINACION -------------|*|\n" <<
		    "   Figuras: |1|Piramide  |2|Cubo  |3|Ply  |4|Revolucion |5|LEGO\n" << 
			"   Modos de dibujado: \n" <<
			"   |p|Puntos   |l|Aristas    |f|Solido   |c|Ajedrez      \n" <<
			"   |i|Iluminacion plana      |s|Iluminacion suave\n" <<
			"\n"
			"   Figura actual: " << figuraToString(figura) << "\n"
			"   Modo actual: " << modoToString(modo) << "\n" <<
			"\n" << endl;
			if (modo == 5 || modo == 6) {
	cout << "   |8|Cambiar material           |9||0|Rotar luz movil\n\n";
	cout << "   Material actual (iluminacion): " << materialToString(material) << "\n";
			} else {
	cout << "\n\n\n";
			}
	cout << "|*|----------------------------------------------------|*|" << endl;

	switch(figura) {
		case 1: lapira.draw(modo, material); break;
		case 2: elcubo.draw(modo, material); break;
		case 3: objeto.draw(modo, material); break;
		//case 4: revo.draw(modo, material); break;
		case 5: legamen.draw(modo, material); break;
		case 6: prepara_textura(); tablo.draw_tablero(20,300, textura_id, true); break;
	}
/*
	switch (modo) {
		case 6: {
			vector<_vertex3f> vertices;
			vertices.resize(11);
			vertices[0].x = 1;   vertices[0].y = -1.4; vertices[0].z = 0;
			vertices[1].x = 1;   vertices[1].y = -1.1; vertices[1].z = 0;
			vertices[2].x = 0.5; vertices[2].y = -0.7; vertices[2].z = 0;
			vertices[3].x = 0.4; vertices[3].y = -0.4; vertices[3].z = 0;
			vertices[4].x = 0.4; vertices[4].y =  0.5; vertices[4].z = 0;
			vertices[5].x = 0.5; vertices[5].y =  0.6; vertices[5].z = 0;
			vertices[6].x = 0.3; vertices[6].y =  0.6; vertices[6].z = 0;
			vertices[7].x = 0.5; vertices[7].y =  0.8; vertices[7].z = 0;
			vertices[8].x = 0.55;vertices[8].y =  1.0; vertices[8].z = 0;
			vertices[9].x = 0.5; vertices[9].y =  1.2; vertices[9].z = 0;
			vertices[10].x= 0.3; vertices[10].y=  1.4; vertices[10].z= 0;

			for (int i = 0; i < vertices.size(); i++) {
				vertices[i].x = vertices[i].x*4;
				vertices[i].y = vertices[i].y*4;
				vertices[i].z = vertices[i].z*4;
			}

			_revolucion revo(vertices, 50, true, true);
			revo.draw_solido(0.5,0.5,1);
			revo.draw_aristas(0,0,0,2);
			if (teclaPulsada == 'p')
				revo.draw_puntos(0.9, 0.23, 0.4, 5);
			else if (teclaPulsada == 'l')
				revo.draw_aristas(0,0,0,2);
			else if (teclaPulsada == 'f') {
				revo.draw_solido(0.5,0.5,1);
				revo.draw_aristas(0,0,0,2);
			} else if (teclaPulsada == 'c') {
				revo.draw_solido_ajedrez(1,0,1,0,1,0);
				revo.draw_aristas(0,0,0,2);
			}
			break;
			}
		case 4: {
			vector<_vertex3f> vertices;
			vertices.resize(3);
			vertices[0].x = 1;   vertices[0].y = -1; vertices[0].z = 0;
			vertices[1].x = 0;   vertices[1].y = 0; vertices[1].z = 0;
			vertices[2].x = 1; vertices[2].y = 1; vertices[2].z = 0;

			for (int i = 0; i < vertices.size(); i++) {
				vertices[i].x = vertices[i].x*3;
				vertices[i].y = vertices[i].y*3;
				vertices[i].z = vertices[i].z*3;
			}

			_revolucion_inv revo(vertices, 6, true, true);
			revo.draw_solido(0.5,0.7,1);
			revo.draw_aristas(0,0,0,2);
			if (teclaPulsada == 'p')
				revo.draw_puntos(0.9, 0.23, 0.4, 5);
			else if (teclaPulsada == 'l')
				revo.draw_aristas(0,0,0,2);
			else if (teclaPulsada == 'f') {
				revo.draw_solido(0.5,0.7,1);
				revo.draw_aristas(0,0,0,2);
			} else if (teclaPulsada == 'c') {
				revo.draw_solido_ajedrez(1,0,1,0,1,0);
				revo.draw_aristas(0,0,0,2);
			}
			break;
			}	
		case 5: legamen.draw(teclaPulsada); break;
	}
	teclaPulsada = '0';
	*/
	glutPostRedisplay();
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
		
	clear_window();
	luces();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
	change_projection();
	glViewport(0, 0, Ancho1, Alto1);
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1, int x, int y)
{
	teclaPulsada = Tecla1;
	if (toupper(Tecla1) == 'Q')
		exit(0);

	switch(Tecla1) {
		case 'p': modo = 1; break;
		case 'l': modo = 2; break;
		case 'f': modo = 3; break;
		case 'c': modo = 4; break;
		case 'i': modo = 5; break;
		case 's': modo = 6; break;
		case 't': modo = 7; break;

		case '1': figura = 1; break;
		case '2': figura = 2; break;
		case '3': figura = 3; break;
		case '4': figura = 4; break;
		case '5': figura = 5; break;
		case '6': figura = 6; break;

		case '9':
			alfa = alfa - 5; break;
		case '0':
			alfa = alfa + 5; break;
		case '7': modelo = (modelo+1)%8;
		case '8': material = (material+1)%18; 
		break;
	}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1, int x, int y)
{

	switch (Tecla1)
	{
	case GLUT_KEY_LEFT:
		Observer_angle_y--;
		break;
	case GLUT_KEY_RIGHT:
		Observer_angle_y++;
		break;
	case GLUT_KEY_UP:
		Observer_angle_x--;
		break;
	case GLUT_KEY_DOWN:
		Observer_angle_x++;
		break;
	case GLUT_KEY_PAGE_UP:
		Observer_distance *= 1.2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Observer_distance /= 1.2;
		break;
	}

	if (modo == 5) {
		switch (Tecla1){
			case GLUT_KEY_F1: legamen.cabeza_atras(); break;
			case GLUT_KEY_F2: legamen.cabeza_adelante(); break;
			case GLUT_KEY_F3: legamen.mano_izq_adelante(); break;
			case GLUT_KEY_F4: legamen.mano_izq_atras(); break;
			case GLUT_KEY_F5: legamen.mano_der_adelante(); break;
			case GLUT_KEY_F6: legamen.mano_der_atras(); break;
			case GLUT_KEY_F7: legamen.legs_up(); break;
			case GLUT_KEY_F8: legamen.legs_down(); break;
			case GLUT_KEY_F9: legamen.alternar_baile(); break;
			case GLUT_KEY_F10:legamen.alternar_reventado(); break;
		}
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Window_width = 5;
	Window_height = 5;
	Front_plane = 10;
	Back_plane = 1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance = 2 * Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	//glClearColor(0.95, 0.95, 0.7, 1);
	glClearColor(1, 1, 1, 1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	//
	change_projection();
	//
	glViewport(0, 0, UI_window_width, UI_window_height);
	
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

	// se llama a la inicialización de glut
	glutInit(&argc, argv);
	srand(time(NULL));

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x, UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width, UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Practica 4 - Iluminacion");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
