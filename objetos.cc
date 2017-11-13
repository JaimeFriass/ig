
#include "objetos.h"
#include "file_ply_stl.h"
using namespace std;


//*************************************************************************
// clase punto
//*************************************************************************
_puntos3D::_puntos3D() {
  }

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
    glPointSize(grosor);
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
    cout << "Se dibujarán " << vertices.size() << " puntos." << endl;
        for (int i=0; i < vertices.size(); i++) {
            glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
        }
    
    glEnd();
}

_triangulos3D::_triangulos3D(){
};

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor) {
    glLineWidth(grosor);
    glColor3f(r,g,b);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    int Vertex1, Vertex2, Vertex3;
        for (int i=0; i < caras.size(); i++) {
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._0]);
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._1]);
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._2]);
        }
    glEnd();
}

void _triangulos3D::draw_solido(float r, float g, float b) {
    glColor3f(r,g,b);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    int Vertex1, Vertex2, Vertex3;
        for (int i=0; i < caras.size(); i++) {
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._0]);
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._1]);
        	glVertex3fv( (GLfloat*) &vertices[caras[i]._2]);
        }
    glEnd();
}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

        for (int i = 0; i < caras.size(); i++) {
            if (i % 2 == 0)
                glColor3f(r1,g1,b1);
            else
                glColor3f(r2,g2,b2);

            glVertex3fv( (GLfloat*) &vertices[caras[i]._0]);
            glVertex3fv( (GLfloat*) &vertices[caras[i]._1]);
            glVertex3fv( (GLfloat*) &vertices[caras[i]._2]);
    }
    glEnd();
}

void _triangulos3D::draw_aristas_circulos(float radio, float n) {

    for (int i = 0; i < vertices.size(); i++) {
        glColor3f(colores[i].r, colores[i].g, colores[i].b);
        Circle(radio, vertices[i].x, vertices[i].y, vertices[i].z, n, GL_FILL);
    }
    
}

void _triangulos3D::Circle(GLfloat radio, GLfloat cx, GLfloat cy, GLfloat cz, GLint n, GLenum modo) {
    if (modo == GL_LINE)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
else if (modo == GL_FILL)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
else
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);


    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) 
        glVertex3f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n), cz);
    glEnd();

}
//    6-------5
//   /|      /|
//  1------0| |
//  | |     | |
//  | |7----|-|4
//  |/      |/
//  2-------3

_cubo::_cubo(float tam) {

    vertices.resize(8);
    vertices[0].x = -tam; vertices[0].y = -tam; vertices[0].z = tam;
    vertices[1].x = tam;   vertices[1].y = -tam; vertices[1].z = tam;
    vertices[2].x = tam;   vertices[2].y = tam;   vertices[2].z = tam;
    vertices[3].x = -tam; vertices[3].y = tam;   vertices[3].z = tam;

    vertices[4].x = -tam; vertices[4].y = -tam;   vertices[4].z = -tam;
    vertices[5].x = tam; vertices[5].y = -tam; vertices[5].z = -tam;
    vertices[6].x = tam;   vertices[6].y = tam; vertices[6].z = -tam;
    vertices[7].x = -tam;   vertices[7].y = tam;   vertices[7].z = -tam;

    caras.resize(16);
    caras.push_back(_vertex3i(0, 1, 4));
    caras.push_back(_vertex3i(1, 5, 4));
    caras.push_back(_vertex3i(1, 2, 5));
    caras.push_back(_vertex3i(2, 6, 5));
    caras.push_back(_vertex3i(2, 3, 6));
    caras.push_back(_vertex3i(3, 7, 6));
    caras.push_back(_vertex3i(3, 0, 7));
    caras.push_back(_vertex3i(0, 4, 7));
    caras.push_back(_vertex3i(4, 5, 7));
    caras.push_back(_vertex3i(5, 6, 7));
    caras.push_back(_vertex3i(3, 2, 0));
    caras.push_back(_vertex3i(2, 1, 0));

    colores.resize(6);
    colores.push_back(_vertex3f(0.1, 0.5, 0.2));
    colores.push_back(_vertex3f(0.2, 0.4, 0.2));
    colores.push_back(_vertex3f(0.3, 0.3, 0.2));
    colores.push_back(_vertex3f(0.4, 0.2, 0.2));
    colores.push_back(_vertex3f(0.5, 0.1, 0.2));
}


//*************************************************************************
// clase triángulo
//*************************************************************************

_piramide::_piramide(float tam, float al) {
    vertices.resize(5);
    vertices[0].x = tam; vertices[0].y = 0; vertices[0].z = -tam;
    vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
    vertices[2].x = -tam; vertices[2].y = 0; vertices[2].z = tam;
    vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;
    vertices[4].x = 0; vertices[4].y = al; vertices[4].z = 0;

    caras.resize(10);
    caras.push_back(_vertex3i(0, 1, 4));
    caras.push_back(_vertex3i(1, 2, 4));
    caras.push_back(_vertex3i(2, 3, 4));
    caras.push_back(_vertex3i(3, 0, 4));
    caras.push_back(_vertex3i(2, 1, 0));
    caras.push_back(_vertex3i(2, 3, 0));

    colores.resize(5);
    colores[0].r = 0.5; colores[0].g = 0.2; colores[0].b = 0.3;
    colores[1].r = 0.4; colores[1].g = 0.3; colores[1].b = 0.3;
    colores[2].r = 0.3; colores[2].g = 0.4; colores[2].b = 0.3;
    colores[3].r = 0.2; colores[3].g = 0.5; colores[3].b = 0.3;
    colores[4].r = 0.1; colores[4].g = 0.6; colores[4].b = 0.3;
}

//*************************************************************************
// clase ply
//*************************************************************************

void _ply::leer(string archivo, float tam) {

    _file_ply file;
    vector<_vertex3f> fvertices;
    vector<_vertex3i> ftriangulos;

    if (file.open(archivo)) {
        file.read(fvertices, ftriangulos);

        for (int i = 0; i < fvertices.size() ; i++) {
            _vertex3f vert;
            vert = fvertices[i];
            vert.x = vert.x*tam;
            vert.y = vert.y*tam;
            vert.z = vert.z*tam;
            vertices.push_back(vert);
        }
    
        for (int i = 0; i < ftriangulos.size() ; i++) {
            _vertex3i car;
            car = ftriangulos[i];
            caras.push_back(car);
        }

        //cout << "Leido\nVertices: " << vertices.size() << "\nCaras: " << caras.size() << endl;

    } else
        cout << "Error al leer el archivo" << endl;
}
_ply::_ply() {
    
}

_ply::_ply(string archivo, float tam) {
    _file_ply file;
    vector<_vertex3f> fvertices;
    vector<_vertex3i> ftriangulos;

    if (file.open(archivo)) {
        file.read(fvertices, ftriangulos);

        for (int i = 0; i < fvertices.size() ; i++) {
            _vertex3f vert;
            vert = fvertices[i];
            vert.x = vert.x*tam;
            vert.y = vert.y*tam;
            vert.z = vert.z*tam;
            vertices.push_back(vert);
        }
    
        for (int i = 0; i < ftriangulos.size() ; i++) {
            _vertex3i car;
            car = ftriangulos[i];
            caras.push_back(car);
        }

        //cout << "Leido\nVertices: " << vertices.size() << "\nCaras: " << caras.size() << endl;

    } else
        cout << "Error al leer el archivo" << endl;
}

////////////////////////
//    REVOLUCION      //
////////////////////////

_revolucion::_revolucion(vector <_vertex3f> perfil, int num, bool tapa_inferior, bool tapa_superior) {

    int num_aux = perfil.size();
    _vertex3i cara_aux;
    _vertex3f vertice_aux;
    vertices.resize(num_aux*num);
    int vertices_cuerpo = num * num_aux;
    
    for (int j = 0; j < num; j++) {
        for (int i = 0; i < num_aux; i++) {
            vertice_aux.x = perfil[i].x * cos(2.0*M_PI*j/(1.0*num)) + perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
            vertice_aux.z = -perfil[i].x * sin(2.0*M_PI*j/(1.0*num)) + perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
            vertice_aux.y = perfil[i].y;

            // Esto viene de la multiplicacion de la rotacion por matrices que sale (x,y,z) (matriz diapositiva) =
            // = (xcos + zcos...)

            vertices[i+j*num_aux] = vertice_aux;
        }
    }

    // tratamiento de las caras
    for (int j = 0; j < num; j++) {
        for (int i = 0; i < num_aux-1; i++) {
            cara_aux._0 = i + ((j+1)%num)*num_aux;
            cara_aux._1 = i + 1 + ((j+1)%num)*num_aux;
            cara_aux._2 = i + 1 + j*num_aux;
            caras.push_back(cara_aux);

            cara_aux._0 = i + 1 + j*num_aux;
            cara_aux._1 = i + j*num_aux;
            cara_aux._2 = i + ((j+1)%num)*num_aux;
            caras.push_back(cara_aux);
        }
    }


    // tapa inferior
    if (tapa_inferior && fabs(perfil[0].x) > 0.0) {
        vertice_aux.y = perfil[0].y;
        vertice_aux.x = 0.0;
        vertice_aux.z = 0.0;
        vertices.push_back(vertice_aux);

        cara_aux._0 = num_aux*num;

        for (int j = 0; j < num; j++) {
            cara_aux._1 = ( (j+1)%num)*num_aux;
            cara_aux._2 = j*num_aux;
            caras.push_back(cara_aux);
        }
    }

    // tapa superior
    if (tapa_superior && fabs(perfil[num_aux-1].x)>0.0) {
        vertice_aux.y = perfil[num_aux-1].y;
        vertice_aux.x = 0.0;
        vertice_aux.z = 0.0;
        vertices.push_back(vertice_aux);

        cara_aux._0 = vertices.size() - 1;
	cara_aux._1 = -1;

        for (int j = 0; j < num; j++) {
	    cara_aux._2 = cara_aux._1 + ((cara_aux._1 < 0) ? vertices_cuerpo : 0);
            cara_aux._1 += num_aux;
            caras.push_back(cara_aux);
        }
    }
}
_revolucion_inv::_revolucion_inv(vector <_vertex3f> perfil, int num, bool tapa_inferior, bool tapa_superior) {
    
        int num_aux = perfil.size();
        _vertex3i cara_aux;
        _vertex3f vertice_aux;
        vertices.resize(num_aux*num);
        int vertices_cuerpo = num * num_aux;
        
        for (int j = 0; j < num; j++) {
            for (int i = 0; i < num_aux; i++) {
                vertice_aux.x = perfil[i].x * cos(2.0*M_PI*j/(1.0*num)) + perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
                vertice_aux.z = -perfil[i].x * sin(2.0*M_PI*j/(1.0*num)) + perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
                vertice_aux.y = perfil[i].y;
    
                // Esto viene de la multiplicacion de la rotacion por matrices que sale (x,y,z) (matriz diapositiva) =
                // = (xcos + zcos...)
    
                vertices[i+j*num_aux] = vertice_aux;
            }
        }
    
        // tratamiento de las caras
        for (int j = 0; j < num; j++) {
            for (int i = 0; i < num_aux-1; i++) {
                if (j%2==1 && perfil[i + ((j+1)%num)*num_aux].y < 0
                    && perfil[i + 1 + j*num_aux].y < 0 ) {
                    cara_aux._0 = i + ((j+1)%num)*num_aux;
                    cara_aux._1 = i + 1 + ((j+1)%num)*num_aux;
                    cara_aux._2 = i + 1 + j*num_aux;
                    caras.push_back(cara_aux);
        
                    cara_aux._0 = i + 1 + j*num_aux;
                    cara_aux._1 = i + j*num_aux;
                    cara_aux._2 = i + ((j+1)%num)*num_aux;
                    caras.push_back(cara_aux);
            }
                if (j%2==0 && perfil[i + ((j+1)%num)*num_aux].y >=0
                    && perfil[cara_aux._0 = i + 1 + j*num_aux].y >=0) {
                    cara_aux._0 = i + ((j+1)%num)*num_aux;
                    cara_aux._1 = i + 1 + ((j+1)%num)*num_aux;
                    cara_aux._2 = i + 1 + j*num_aux;
                    caras.push_back(cara_aux);
        
                    cara_aux._0 = i + 1 + j*num_aux;
                    cara_aux._1 = i + j*num_aux;
                    cara_aux._2 = i + ((j+1)%num)*num_aux;
                    caras.push_back(cara_aux);
                }
            }
        }
    
    
        // tapa inferior
        if (tapa_inferior && fabs(perfil[0].x) > 0.0) {
            vertice_aux.y = perfil[0].y;
            vertice_aux.x = 0.0;
            vertice_aux.z = 0.0;
            vertices.push_back(vertice_aux);
    
            cara_aux._0 = num_aux*num;
    
            for (int j = 0; j < num; j++) {
                cara_aux._1 = ( (j+1)%num)*num_aux;
                cara_aux._2 = j*num_aux;
                caras.push_back(cara_aux);
            }
        }
    
        // tapa superior
        if (tapa_superior && fabs(perfil[num_aux-1].x)>0.0) {
            vertice_aux.y = perfil[num_aux-1].y;
            vertice_aux.x = 0.0;
            vertice_aux.z = 0.0;
            vertices.push_back(vertice_aux);
    
            cara_aux._0 = vertices.size() - 1;
        cara_aux._1 = -1;
    
            for (int j = 0; j < num; j++) {
            cara_aux._2 = cara_aux._1 + ((cara_aux._1 < 0) ? vertices_cuerpo : 0);
                cara_aux._1 += num_aux;
                caras.push_back(cara_aux);
            }
        }
    }


/////////////////////////////////////////////////////////////////
//                       CONSTRUCTORES

void inicializar() {
    
    glTranslatef(0.7,0,3.4);
    glRotatef(-90,1,0,0);
    
}

void colocar(bool reventado) {
    if (reventado) {
        int num = rand()%7;
        int coord = rand()%5;
        int rot = rand()%5;

        switch (coord) {
            case 0: glTranslatef(-num,0,0); glRotatef(-num/2,0,1,0); break;
            case 1: glTranslatef(0,+num,num/2); break;
            case 2: glTranslatef(num/3,0,-num); break;
            case 3: glTranslatef(-num,-num/2,0); break;
            case 4: glTranslatef(0,0,-num); break;
        }
        num = num*5;
        switch (rot) {
            case 0: glRotatef(-num/3,0,0,1); break;
            case 1: glRotatef(num,1,0,0); break;
            case 2: glRotatef(num,0,1,0); break;
            case 3: glRotatef(num,0,0,1); break;
            case 4: glRotatef(-num,1,1,0); break;
        }
    }
    glTranslatef(0,-5.5,0);
}

_cabeza::_cabeza() {
    glPushMatrix();
        _ply cabezon;
        glTranslatef(0,-9.3,0); // Traslado al eje
        inicializar();
        cabezon.leer("./lego_ply/cabeza.ply", 0.08);
        cabezon.draw_aristas(0,0,0,1);
        cabezon.draw_solido(0.95,0.95,0.05);
    glPopMatrix();

}

_pierna::_pierna() {
    
    glPushMatrix();
        _ply pierna;
        glTranslatef(0,-4.5,0.2);
        glTranslatef(0,2,3.4);
        glRotatef(-53, 1, 0, 0);
        inicializar();
        pierna.leer("./lego_ply/pierna.ply", 0.08);
        pierna.draw_aristas(0,0,0,1);
        pierna.draw_solido(0.4,0.5,0.2);
    glPopMatrix();

}

_mano_izq::_mano_izq() {
    glPushMatrix();
    _ply mano;
    glTranslatef(0,-8.75,-0.1); // Translado al eje
    inicializar();
    mano.leer("./lego_ply/mano_izq.ply", 0.08);
    mano.draw_aristas(0,0,0,1);
    mano.draw_solido(0.95,0.95,0.05);
    glPopMatrix();

}

_mano_der::_mano_der() {
    glPushMatrix();

    _ply mano;
    glTranslatef(0,-8.75,-0.1); // Translado al eje
    inicializar();
    mano.leer("./lego_ply/mano_der.ply", 0.08);
    mano.draw_aristas(0,0,0,1);
    mano.draw_solido(0.95,0.95,0.05);
    glPopMatrix();

}

_pecho::_pecho() {
    glPushMatrix();
    _ply pecho;
    inicializar();
    pecho.leer("./lego_ply/pecho.ply", 0.08);
    pecho.draw_aristas(0,0,0,1);
    pecho.draw_solido(0.4,1,0.2);
    glPopMatrix();
}

_lego::_lego() {

    // Iniciamos todas las posibilidades de movimiento a 0.
    for (int i = 0; i < 6; i++)
       this->mov[i] = 0;
        
    baile = false;
    reventado = false;
}

///////////////////////////////////////////////////////////
//                         DRAW LEGO

void _lego::draw() {
    if (baile)
        bailar();

        float lu = mov[LU];
        float lhu = mov[LHAND];
        float rhu = mov[RHAND];
        float head = mov[HEAD];

        // PECHO
        glPushMatrix();
            colocar(reventado);
            _pecho *pechamen = new _pecho;
        glPopMatrix();

        // CABEZA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,9.3,0); // Traslado al eje inverso
            glRotatef(head,1,0,0); // Movimiento
            glPushMatrix();
                _cabeza *cabezon = new _cabeza;
            glPopMatrix();
        glPopMatrix();

        // MANO IZQUIERDA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,8.75,0.1); // Translado al eje inverso
            glRotatef(lhu, 1, 0, 0);
            glPushMatrix();
                _mano_izq *manoizq = new _mano_izq;
            glPopMatrix();
        glPopMatrix();

        // MANO DERECHA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,8.75,0.1); // Translado al eje inverso
            glRotatef(rhu, 1, 0 , 0);   // Rotamiento
            glPushMatrix();
                _mano_der *manoder = new _mano_der;
            glPopMatrix();
        glPopMatrix();

        // PIERNAS
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,4.5,-0.2);
            glRotatef(lu, 1, 0, 0);     // Rotamiento
            glPushMatrix();
                _pierna *pierna1 = new _pierna;
                glTranslatef(-2.6,0,0);
                _pierna *pierna2 = new _pierna;
            glPopMatrix();
        glPopMatrix();



}
//////////////////////////////////////////////////////////
//                      REVENTAR

void _lego::alternar_reventado() {
    if (reventado) reventado = false; else reventado = true;
}

//////////////////////////////////////////////////////////
//                      MOVIMIENTOS
void _lego::alternar_baile() {
    if (baile) baile = false; else baile = true;
}
void _lego::bailar() {

    int num= (TOPE_MANO_ADELANTE +rand()%(TOPE_MANO_ATRAS-TOPE_MANO_ADELANTE))*0.2;
    cout << "[BAILE] Generado num1 = " << num << " +/- " << mov[LU] << endl;
    int atras = rand()%2;

    if (atras && TOPE_MANO_ADELANTE > mov[LU]+num)
        mov[LU] += num;
    else if (TOPE_MANO_ATRAS < mov[LU]-num)
        mov[LU] -= num;
    else
        mov[LU] += 1;
    
    num= (TOPE_CABEZA_ADELANTE +rand()%(TOPE_CABEZA_ATRAS-TOPE_CABEZA_ADELANTE))*0.2;
    cout << "[BAILE] Generado num2 = " << num << " +/- " << mov[HEAD] << endl;
    atras = rand()%2;
    if (atras && TOPE_CABEZA_ADELANTE > mov[HEAD]+num)
        mov[HEAD] += num;
    else if (TOPE_CABEZA_ATRAS < mov[HEAD]-num)
        mov[HEAD] -= num;
    else
        mov[HEAD] += 1;
    

}
void _lego::legs_up() {
    if (mov[LU] < TOPE_PIES_ADELANTE) {
        mov[LU] += 3;
        cout << "Piernas arriba. mov[LU] = "<< mov[LU] << endl;
    } else {
        cout << "Limite de piernas adelante." << endl;
    }
}

void _lego::legs_down() {
    if (mov[LU] > TOPE_PIES_ATRAS) {
        mov[LU] -= 3;
        cout << "Piernas abajo. mov[LU] = " << mov[LU] << endl;
    } else {
        cout << "Limite de piernas atras." << endl;
    }
}

// MANO DERECHA
void _lego::mano_der_adelante() {
    if (mov[RHAND] < TOPE_MANO_ADELANTE) {
        mov[RHAND] += 3;
        cout << "Mano derecha arriba. mov[RHAND] = " << mov[RHAND] << endl;
    } else {
        cout << "Mano derecha ha llegado al tope de arriba" << endl;
    }
}
void _lego::mano_der_atras() {
    if (mov[RHAND] > TOPE_MANO_ATRAS) {
        mov[RHAND] -= 3;
        cout << "Mano derecha abajo. mov[RHAND] = " << mov[RHAND] << endl;
    } else {
        cout << "Mano derecha ha llegado al tope de abajo." << endl;
    }
}

// MANO IZQUIERDA
void _lego::mano_izq_adelante() {
    if (mov[LHAND] < TOPE_MANO_ADELANTE)
        mov[LHAND] += 3;
}
void _lego::mano_izq_atras() {
    if (mov[LHAND] > TOPE_MANO_ATRAS)
        mov[LHAND] -= 3;
}

// CABEZON
void _lego::cabeza_atras() {
    if (mov[HEAD] < TOPE_CABEZA_ADELANTE) {
        mov[HEAD] += 3;
        cout << "CABEZA ARRIBA:" << mov[HEAD] << endl;
    } else {
        cout << "Cabeza arriba ha llegado al tope";
    }
}
void _lego::cabeza_adelante() {
    if (mov[HEAD] > TOPE_CABEZA_ATRAS) {
        mov[HEAD] -= 3;
    }
}


