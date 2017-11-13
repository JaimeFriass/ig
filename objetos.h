//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <math.h>
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
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void draw_aristas_circulos(float radio, float n);
	void Circle(GLfloat radio, GLfloat cx, GLfloat cy, GLfloat cz, GLint n, GLenum modo);

	vector<_vertex3i> caras;
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
	 void draw();

	 GLfloat mov[QUIT];
 };

class _cabeza : public _ply
{
public:
	_cabeza();
	void draw(float r1, float g1, float b1);
};

class _pierna : public _ply
{
public:
	_pierna();
};

class _mano_izq : public _ply
{
public:
	_mano_izq();
};

class _mano_der : public _ply
{
public:
	_mano_der();
};

class _pecho : public _ply
{
public:
	_pecho();
};
