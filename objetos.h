//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

using namespace std;

//const float AXIS_SIZE = 5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
  public:
	_puntos3D();
	void draw_puntos(float r, float g, float b, int grosor);

	vector<_vertex3f> vertices;
	vector<_vertex3f> colores;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
  public:
	_triangulos3D();

	void draw(const int &modo, const int &material);
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void draw_aristas_circulos(float radio, float n);
	void Circle(GLfloat radio, GLfloat cx, GLfloat cy, GLfloat cz, GLint n, GLenum modo);
	
	void calcular_normales_vertices();
	void calcular_normales_caras();
	void draw_textura(GLuint ident_textura);
	void draw_iluminacion_suave(const int &material);
	void draw_iluminacion_plana(const int &material);
	void draw_textura_iluminacion_plana(GLuint ident_textura);
	void draw_textura_iluminacion_suave(GLuint ident_textura);

	vector<_vertex3i> caras;

	vector<_vertex3f> normales_caras;
	vector<_vertex3f> normales_vertices;
	vector<_vertex3f> textura_coord;

	bool b_normales_caras = false;
	bool b_normales_vertices = false;
	bool b_textura_coord;

	// Materiales
	// 1 - Brass
	// 2 - Bronze
	// 3 - Polished Bronze
	// 4 - Chrome
	// 5 - Copper
	// 6 - Polished Copper
	// 7 - Gold
	// 8 - Polished Gold
	// 9 - Silver
	// 10- Polished Silver
	// 11- Emerald
	// 12- Jade
	// 13- Obsidian
	// 14- Pearl
	// 15- Ruby
	// 16- Turquoise
	// 17- Black Plastic
	// 18- Black Rubber

	_vertex4f ambiente_difusa[18] = {{0.78, 0.56, 0.11, 1.0},
									{0.7, 0.42, 0.18, 1.0},
									{0.4, 0.23, 0.10, 1.0},
									{0.4 , 0.4, 0.4, 1.0},
									{0.70, 0.27, 0.08, 1}, // Copper
									{0.55,0.2,0.06,1.0},
									{0.75, 0.60, 0.22, 1.0}, // Gold
									{0.34, 0.31, 0.09, 1.0},
									{0.507, 0.507, 0.507, 1.0}, // Silver
									{0.277, 0.277, 0.277, 1.0},
									{0.07, 0.614, 0.07, 0.55},
									{0.54, 0.89, 0.63, 0.95}, // Jade
									{0.18, 0.17, 0.225, 0.82},
									{1.0, 0.82, 0.82, 0.922}, // Pearl
									{0.614, 0.041, 0.041, 0.55}, // Runy
									{0.396, 0.741, 0.69, 0.8},
									{0.01,0.01,0.01,1.0}, // Black Plastic
									{0.01, 0.01, 0.01, 1.0}}; // Black Rubber
	
	// Coeficientes ambiente y difuso
	_vertex4f especular[18] =  {{0.992, 0.941, 0.807, 1.0},
							   {0.393, 0.271, 0.166, 1.0},
							   {0.774, 0.45, 0.2, 1.0}, // Polished Bronze
							   {0.774, 0.774, 0.774, 1.0}, // Chrome
							   {0.256, 0.137, 0.08, 1.0}, // Copper
							   {0.58, 0.223, 0.069, 1.0}, // Gold
							   {0.62, 0.555, 0.36, 1.0}, // Polished Gold
							   {0.508, 0.508, 0.508, 1.0},
							   {0.773, 0.773, 0.773, 1.0}, // Polished Silver
							   {0.633, 0.727, 0.633, 0.55}, // Emerald
							   {0.31, 0.31, 0.31, 0.95}, // Jade
						       {0.33, 0.32, 0.34, 0.82}}; // Obsidian
	float brillo[18] = { 27.89, 25.6, 76.8, 76.8, 12.8, 51.2, 51.2, 51.2, 83.2, 51.2, 89.6, 76.8, 12.8, 38.4, 11.2, 76.8, 12.8, 32}; 			   // Exponente del brillo

	bool modo_text;            // Generación automática o no de las coords de textura
	GLfloat plano_s[4];        // Si modo_text=true se usan esttos coeficientes
	GLfloat plano_t[4];		   //Generación automática de las coords de textura
	

};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
  public:
	_cubo(float tam = 0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
  public:
	_piramide(float tam = 0.5, float al = 0.75);
};

//*************************************************************************
// clase PLY
//*************************************************************************

class _ply : public _triangulos3D
{
public:
	_ply();
	_ply(string archivo, float tam);
	void leer(string archivo, float tam);
};

class _revolucion : public _triangulos3D
{
public:
	_revolucion(vector<_vertex3f> perfil, int num, bool tapa_inferior, bool tapa_superior);
	vector<_vertex3f> leer_ply(string archivo);
};


class _revolucion_inv : public _triangulos3D
{
public:
	_revolucion_inv(vector<_vertex3f> perfil, int num, bool tapa_inferior, bool tapa_superior);
};

 /////////////////////////
// Objeto articulado     //
//       LEGO			 //
 /////////////////////////

// Rota el lego y lo coloca sobre los ejes
void inicializar();

// Coloca el lego más abajo para una mejor visión. Si esta reventado de forma
// aleatoria se desplazará y se rotará hasta que se desactive este modo.
void colocar(bool reventado);

class _lego : public _triangulos3D
 {
 public:
	 _lego();

	 const static int TOPE_MANO_ADELANTE = 100;
	 const static int TOPE_MANO_ATRAS    = -100;
	 const static int TOPE_CABEZA_ADELANTE   = 20;
	 const static int TOPE_CABEZA_ATRAS      = -30;
	 const static int TOPE_PIES_ADELANTE     = 50;
	 const static int TOPE_PIES_ATRAS        = -50;

	 enum {
		 TORSO = 0,
		 LU, // legs up
		 RHAND, // right hand up
		 LHAND, // left hand up
		 HEAD,  // rotate head left
		 QUIT,
	 };
	 

	 // Modo descomposición.
	 void alternar_reventado();
	 bool reventado;
	 bool muerto;

	 // Modo baile
	 void bailar();
	 void alternar_baile();
	 bool baile;

	 // Funciones de movimiento
	 void legs_up();
	 void legs_down();
	 void mano_der_adelante();
	 void mano_der_atras();
	 void mano_izq_adelante();
	 void mano_izq_atras();
	 void cabeza_atras();
	 void cabeza_adelante();

	 void head();
	 void torso();
	 void left_hand();
	 void right_hand();
	 void legs();

	 // Función principal, se actualizará continuamente.
	 void draw(char modo);

	 GLfloat mov[QUIT];
 };

class _cabeza : public _ply
{
public:
	_cabeza(char modo);
	void draw(float r1, float g1, float b1);
};

class _pierna : public _ply
{
public:
	_pierna(char modo);
};

class _mano_izq : public _ply
{
public:
	_mano_izq(char modo);
};

class _mano_der : public _ply
{
public:
	_mano_der(char modo);
};

class _pecho : public _ply
{
public:
	_pecho(char modo);
};
