
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

_cabeza::_cabeza(const int &modo, const int &material) {
    glPushMatrix();
        _ply cabezon;
        glTranslatef(0,-9.3,0); // Traslado al eje
        inicializar();
        cabezon.leer("./lego_ply/cabeza.ply", 0.08);
        switch(modo) {
            case 1:
                cabezon.draw_puntos(0,0,0,5);
                break;
            case 2:
                cabezon.draw_aristas(0,0,0,2);
                break;
            case 3:
                cabezon.draw_solido(1,0.50,0.9);
                cabezon.draw_aristas(0,0,0,2);
                break;
            case 4:
                cabezon.draw_solido_ajedrez(1,0,0,0,1,0);
                cabezon.draw_aristas(0,0,0,2);
                break;
            case 5:
                cabezon.draw_iluminacion_plana(material); break;
            case 6:
                cabezon.draw_iluminacion_suave(material); break;
            default:
                cabezon.draw_aristas(0,0,0,1);
                cabezon.draw_solido(0.95,0.95,0.05);
                break;
        }

    glPopMatrix();

}

_pierna::_pierna(const int &modo, const int &material) {
    
    glPushMatrix();
        _ply pierna;
        glTranslatef(0,-4.5,0.2);
        glTranslatef(0,2,3.4);
        glRotatef(-53, 1, 0, 0);
        inicializar();
        pierna.leer("./lego_ply/pierna.ply", 0.08);

        switch(modo) {
            case 1:
                pierna.draw_puntos(0,0,0,2);
                break;
            case 2:
                pierna.draw_aristas(0,0,0,2);
                break;
            case 3:
                pierna.draw_solido(1,0.50,0.9);
                pierna.draw_aristas(0,0,0,2);
                break;
            case 4:
                pierna.draw_solido_ajedrez(1,0,0,0,1,0);
                pierna.draw_aristas(0,0,0,2);
                break;
            case 5:
                pierna.draw_iluminacion_plana(material); break;
            case 6:
                pierna.draw_iluminacion_suave(material); break;
            default:
                pierna.draw_aristas(0,0,0,1);
                pierna.draw_solido(0.4,0.5,0.2);
                break;
        }

    glPopMatrix();

}

_mano_izq::_mano_izq(const int &modo, const int &material) {
    glPushMatrix();
    _ply mano;
    glTranslatef(0,-8.75,-0.1); // Translado al eje
    inicializar();
    mano.leer("./lego_ply/mano_izq.ply", 0.08);
        switch(modo) {
            default:
                mano.draw_aristas(0,0,0,1);
                mano.draw_solido(0.95,0.95,0.05);
                break;
            case 1:
                mano.draw_puntos(0,0,0,2);
                break;
            case 2:
                mano.draw_aristas(0,0,0,2);
                break;
            case 3:
                mano.draw_solido(1,0.50,0.9);
                mano.draw_aristas(0,0,0,2);
                break;
            case 4:
                mano.draw_solido_ajedrez(1,0,0,0,1,0);
                mano.draw_aristas(0,0,0,2); break;
            case 5:
                mano.draw_iluminacion_plana(material); break;
            case 6:
                mano.draw_textura_iluminacion_suave(material); break;

        }


    glPopMatrix();

}

_mano_der::_mano_der(const int &modo, const int &material) {
    glPushMatrix();
    _ply mano;
    glTranslatef(0,-8.75,-0.1); // Translado al eje
    inicializar();
    mano.leer("./lego_ply/mano_der.ply", 0.08);
        switch(modo) {
            default: mano.draw_aristas(0,0,0,1); mano.draw_solido(0.95,0.95,0.05); break;
            case 1: mano.draw_puntos(0,0,0,2); break;
            case 2: mano.draw_aristas(0,0,0,2); break;
            case 3: mano.draw_solido(1,0.50,0.9); mano.draw_aristas(0,0,0,2); break;
            case 4: mano.draw_solido_ajedrez(1,0,0,0,1,0); mano.draw_aristas(0,0,0,2); break;
            case 5: mano.draw_iluminacion_plana(material); break;
            case 6: mano.draw_iluminacion_suave(material); break;
        }
    glPopMatrix();

}

_pecho::_pecho(const int &modo, const int &material) {
    glPushMatrix();
    _ply pecho;
    inicializar();
    pecho.leer("./lego_ply/pecho.ply", 0.08);
        switch(modo) {
            default: pecho.draw_aristas(0,0,0,1); pecho.draw_solido(0.4,1,0.2); break;
            case 1: pecho.draw_puntos(0,0,0,2); break;
            case 2: pecho.draw_aristas(0,0,0,2); break;
            case 3: pecho.draw_solido(1,0.50,0.9); pecho.draw_aristas(0,0,0,2); break;
            case 4: pecho.draw_solido_ajedrez(1,0,0,0,1,0); pecho.draw_aristas(0,0,0,2); break;
            case 5: pecho.draw_iluminacion_plana(material); break;
            case 6: pecho.draw_iluminacion_suave(material); break;
        }
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

void _lego::draw(const int &modo, const int &material) {
    if (baile)
        bailar();

        float lu = mov[LU];
        float lhu = mov[LHAND];
        float rhu = mov[RHAND];
        float head = mov[HEAD];

        // PECHO
        glPushMatrix();
            colocar(reventado);
            _pecho *pechamen = new _pecho(modo, material);
        glPopMatrix();

        // CABEZA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,9.3,0); // Traslado al eje inverso
            glRotatef(head,1,0,0); // Movimiento
            glPushMatrix();
                _cabeza *cabezon = new _cabeza(modo, material);
            glPopMatrix();
        glPopMatrix();

        // MANO IZQUIERDA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,8.75,0.1); // Translado al eje inverso
            glRotatef(lhu, 1, 0, 0);
            glPushMatrix();
                _mano_izq *manoizq = new _mano_izq(modo, material);
            glPopMatrix();
        glPopMatrix();

        // MANO DERECHA
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,8.75,0.1); // Translado al eje inverso
            glRotatef(rhu, 1, 0 , 0);   // Rotamiento
            glPushMatrix();
                _mano_der *manoder = new _mano_der(modo, material);
            glPopMatrix();
        glPopMatrix();

        // PIERNAS
        glPushMatrix();
            colocar(reventado);
            glTranslatef(0,4.5,-0.2);
            glRotatef(lu, 1, 0, 0);     // Rotamiento
            glPushMatrix();
                _pierna *pierna1 = new _pierna(modo, material);
                glTranslatef(-2.6,0,0);
                _pierna *pierna2 = new _pierna(modo, material);
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

    int num= (TOPE_MANO_ADELANTE +rand()%(TOPE_MANO_ATRAS-TOPE_MANO_ADELANTE))*0.1;
    //cout << "[BAILE] Generado num1 = " << num << " +/- " << mov[LU] << endl;
    int atras = rand()%2;

    if (atras && TOPE_MANO_ADELANTE > mov[LU]+num)
        mov[LU] += num;
    else if (TOPE_MANO_ATRAS < mov[LU]-num)
        mov[LU] -= num;
    else
        mov[LU] += 1;
    
    num= (TOPE_CABEZA_ADELANTE +rand()%(TOPE_CABEZA_ATRAS-TOPE_CABEZA_ADELANTE))*0.1;
    //cout << "[BAILE] Generado num2 = " << num << " +/- " << mov[HEAD] << endl;
    atras = rand()%2;
    if (atras && TOPE_CABEZA_ADELANTE > mov[HEAD]+num)
        mov[HEAD] += num;
    else if (TOPE_CABEZA_ATRAS < mov[HEAD]-num)
        mov[HEAD] -= num;
    else
        mov[HEAD] += 1;

    num= (TOPE_MANO_ADELANTE +rand()%(TOPE_MANO_ADELANTE-TOPE_MANO_ATRAS))*0.1;
    //cout << "[BAILE] Generado num2 = " << num << " +/- " << mov[HEAD] << endl;
    atras = rand()%2;
    if (atras && TOPE_MANO_ADELANTE > mov[RHAND]+num)
        mov[RHAND] += num;
    else if (TOPE_MANO_ATRAS < mov[HEAD]-num)
        mov[RHAND] -= num;
    else
        mov[RHAND] += 1;
    
    num= (TOPE_MANO_ADELANTE +rand()%(TOPE_MANO_ADELANTE-TOPE_MANO_ATRAS))*0.1;
    //cout << "[BAILE] Generado num2 = " << num << " +/- " << mov[HEAD] << endl;
    atras = rand()%2;
    if (atras && TOPE_MANO_ADELANTE > mov[RHAND]+num)
        mov[LHAND] += num;
    else if (TOPE_MANO_ATRAS < mov[HEAD]-num)
        mov[LHAND] -= num;
    else
        mov[LHAND] += 1;
    usleep(100000);

}
void _lego::legs_up() {
    if (mov[LU] < TOPE_PIES_ADELANTE) {
        mov[LU] += 3;
    }
}

void _lego::legs_down() {
    if (mov[LU] > TOPE_PIES_ATRAS) {
        mov[LU] -= 3;
    }
}

// MANO DERECHA
void _lego::mano_der_adelante() {
    if (mov[RHAND] < TOPE_MANO_ADELANTE) {
        mov[RHAND] += 3;

    }
}
void _lego::mano_der_atras() {
    if (mov[RHAND] > TOPE_MANO_ATRAS) {
        mov[RHAND] -= 3;
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
    }
}
void _lego::cabeza_adelante() {
    if (mov[HEAD] > TOPE_CABEZA_ATRAS) {
        mov[HEAD] -= 3;
    }
}

//////////////////////////////////////////////////
//           LUCES
//////////////////////////////////////////////////


void _triangulos3D::draw(const int &modo, const int &material) {
    switch(modo) {
        case 1: draw_puntos(0, 0, 0, 5); break;		
		case 2: draw_aristas(0.0, 0.0, 0.0, 1);
        case 3: draw_solido(0.2, 0.95, 0.7); 
                draw_aristas(0,0,0,1); break;
		case 4: draw_solido_ajedrez(0.87, 0.67, 0.95, 0.95, 0.65, 0.87); 
                draw_aristas(0,0,0,1); break;
		case 5: draw_iluminacion_plana(material); break;
		case 6: draw_iluminacion_suave(material); break;
		case 7: draw_textura(0); break;
    }
}
// Cálculo de las normales de las caras
/*
void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());

	for (unsigned long i = 0; i < caras.size(); i++){
		// Obtenemos dos vectores en el triángulo y calculamos el producto vectorial
		_vertex3f a1 = vertices[caras[i]._1] - vertices[caras[i]._0],
				  a2 = vertices[caras[i]._2] - vertices[caras[i]._0],
				  n = a1.cross_product(a2);
		// Módulo
		float m = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
		// Normalizamos
		normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
	}

	b_normales_caras = true;
}

*/

// RUIDO NORMAL
int nrand;
float ga, gf;
void initgauss() {
    nrand = 4;
    ga=sqrt(3.0*nrand);
    gf = 2*ga/(RAND_MAX*1.0);
    srandom(3);
}

float gauss() {
    float sum;
    int i;
    sum = 0.0;
    for (i=0; i < nrand; i++) sum = sum + random();
    return gf*sum/nrand-ga;
}
void    _triangulos3D::calcular_normales_caras(){
    initgauss(); 
    for(int i =0 ; i < caras.size() ; i++){ 
        _vertex3f vector1(vertices[caras[i]._1].x*gauss() - vertices[caras[i]._0].x, 
                        vertices[caras[i]._1].y*gauss() - vertices[caras[i]._0].y, 
                        vertices[caras[i]._1].z*gauss() - vertices[caras[i]._0].z); 
 
        _vertex3f vector2(vertices[caras[i]._2].x*gauss() - vertices[caras[i]._0].x, 
                        vertices[caras[i]._2].y*gauss() - vertices[caras[i]._0].y, 
                        vertices[caras[i]._2].z*gauss() - vertices[caras[i]._0].z); 
         
        _vertex3f normal( (vector1.y*vector2.z)*gauss() - (vector1.z*vector2.y), 
                        (vector1.y*vector2.x)*gauss() - (vector1.x*vector2.z), 
                        (vector1.x*vector2.y)*gauss() - (vector1.y*vector2.x)); 
        normales_caras.push_back(normal); 
             
    } 
    b_normales_caras=true; 
}

// Cálculo de las normales de los vértices


void _triangulos3D::calcular_normales_vertices(){
    
    if(b_normales_vertices==false){
        if(b_normales_caras ==false)
            calcular_normales_caras();
        normales_vertices.resize(vertices.size());
        for(int i =0 ; i< caras.size() ; i++){
            normales_vertices[caras[i]._0].x += normales_caras[i].x;
            normales_vertices[caras[i]._0].y += normales_caras[i].y;
            normales_vertices[caras[i]._0].z += normales_caras[i].z;

            normales_vertices[caras[i]._1].x += normales_caras[i].x;
            normales_vertices[caras[i]._1].y += normales_caras[i].y;
            normales_vertices[caras[i]._1].z += normales_caras[i].z;

            normales_vertices[caras[i]._2].x += normales_caras[i].x;
            normales_vertices[caras[i]._2].y += normales_caras[i].y;
            normales_vertices[caras[i]._2].z += normales_caras[i].z;
        }
    }
    b_normales_vertices=true;
}

// Dibujar con iluminación y sin suavizado. Terminada
void _triangulos3D::draw_iluminacion_plana(const int &material){
	int i;
	GLfloat ambient_component[4]={1,1,1,1};

	if (!b_normales_caras)
		calcular_normales_caras();

	//glEnable(GL_CULL_FACE);
	//glLightmOdelfv(GL_LIGHT_MODEL_AMBIENT, ambient_component);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa[material]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular[material]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo[material]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i = 0; i < caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
	//glDisable(GL_CULL_FACE);
}

// Dibujar con iluminación y con suavizado. Terminada
void _triangulos3D::draw_iluminacion_suave(const int &material){
	int i;
	GLfloat ambient_component[4]={1,1,1,1};

	if (!b_normales_vertices)
		calcular_normales_vertices();

	//glEnable(GL_CULL_FACE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_component);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa[material]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular[material]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo[material]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i = 0; i < caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
	//glDisable(GL_CULL_FACE);

}


void _triangulos3D::draw_textura(GLuint ident_textura) {
    // Activación de la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ident_textura);
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (modo_text == true) {
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_S, GL_EYE_PLANE, plano_s);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_T, GL_EYE_PLANE, plano_t);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++) {
        glNormal3fv((GLfloat *) &normales_caras[i]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._0].s, textura_coord[caras[i]._0].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._1].s, textura_coord[caras[i]._1].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._2].s, textura_coord[caras[i]._2].s);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }


    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glEnable(GL_LIGHTING);
}
// Dibujar con textura, iluminación y SIN suavizado
void _triangulos3D::draw_textura_iluminacion_plana(GLuint ident_textura) {
    GLfloat material_blanco[4] = {1,1,1,1};

    if (b_normales_caras == false) calcular_normales_caras();
    // Activar iluminación
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_blanco);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular[0]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo[0]);

    // Activación de la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ident_textura); // Vínculo con la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (modo_text == true) {
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_S, GL_EYE_PLANE, plano_s);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_T, GL_EYE_PLANE, plano_t);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++) {
        glNormal3fv((GLfloat *) &normales_caras[i]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._0].s, textura_coord[caras[i]._0].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._1].s, textura_coord[caras[i]._1].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        if (b_textura_coord == true)
            glTexCoord2f(textura_coord[caras[i]._2].s, textura_coord[caras[i]._2].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glEnable(GL_LIGHTING);
}

// Dibujar con textura, iluminación y suavizado

void _triangulos3D::draw_textura_iluminacion_suave(GLuint ident_textura){
	GLfloat material_blanco[4]={1.0, 1.0, 1.0, 1};

	if (!b_normales_vertices) 
		calcular_normales_vertices();

	// Activación de iluminación
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_blanco);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular[0]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo[0]);

	// activación de la textura
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ident_textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generación automática de texturas
	if (modo_text){
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv(GL_S, GL_OBJECT_PLANE, plano_s);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, plano_t);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
		
		if (b_textura_coord)
			glTexCoord2f(textura_coord[caras[i]._0].s, textura_coord[caras[i]._0].t);
		
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);

		if (b_textura_coord)
			glTexCoord2f(textura_coord[caras[i]._1].s, textura_coord[caras[i]._1].t);

		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);

		if (b_textura_coord)
			glTexCoord2f(textura_coord[caras[i]._2].s, textura_coord[caras[i]._2].t);

		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING);
}


// textura
/*
void tablero_textura(float lado, int n) {
    int i,j;
    glPolyGonMode(GL_FRONT_AND_BACK, GL_FILL)

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            glBegin(GL_POLYGON);
                glTexCoor2d()
                glVertex3f(j*lado/(1.0*n),i*lado/(1.0*n), 0.0);

            glEnd();
    }
}
*/


//*********************************************************************
// clase tablero
//*********************************************************************

_tablero::_tablero(){}

void _tablero::draw_tablero(float lado, int n, GLuint textura_id, bool transpuesta){
  glDisable(GL_LIGHTING);
  glDisable(GL_NORMALIZE);
  glColor3f(1, 1, 1);

  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textura_id);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      glBegin(GL_POLYGON);

      if (!transpuesta){
        glTexCoord2d(j/(1.0*n), (n - i)/(1.0*n));
        glVertex3f(j*lado/(1.0*n), i*lado/(1.0*n), 0.0);
        glVertex3f((j+1)*lado/(1.0*n), i*lado/(1.0*n), 0.0);
        glVertex3f((j+1)*lado/(1.0*n), (i+1.0)*lado/(1.0*n), 0.0);
        glVertex3f(j*lado/(1.0*n), (i+1.0)*lado/(1.0*n), 0.0);
      }
      else {
        glTexCoord2d((n-i)/(1.0*n), j/(1.0*n));
        glVertex3f(i*lado/(1.0*n), j*lado/(1.0*n), 0.0);
        glVertex3f(i*lado/(1.0*n), (j+1)*lado/(1.0*n), 0.0);
        glVertex3f((i+1.0)*lado/(1.0*n), (j+1)*lado/(1.0*n), 0.0);
        glVertex3f((i+1.0)*lado/(1.0*n), j*lado/(1.0*n), 0.0);  
      }

      glEnd();
      }
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

