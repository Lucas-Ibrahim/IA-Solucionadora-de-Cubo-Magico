#include "cubo_visual.h"
#include <GLFW/glfw3.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif
#include <cmath>
#include <vector>
#include <algorithm>

const float PI = 3.14159265f;

//Estruturas Matemáticas
struct Vec3 { float x, y, z; }; 
struct Mat3 { float m[3][3]; }; 

Vec3 mulMatVec(const Mat3& a, const Vec3& v) {
    return {
        a.m[0][0]*v.x + a.m[0][1]*v.y + a.m[0][2]*v.z,
        a.m[1][0]*v.x + a.m[1][1]*v.y + a.m[1][2]*v.z,
        a.m[2][0]*v.x + a.m[2][1]*v.y + a.m[2][2]*v.z
    };
}

Mat3 mulMatMat(const Mat3& a, const Mat3& b) { 
    Mat3 r{};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            r.m[i][j] = a.m[i][0]*b.m[0][j] + a.m[i][1]*b.m[1][j] + a.m[i][2]*b.m[2][j];
    return r;
}

Mat3 matIdentidade() { return {{{1,0,0},{0,1,0},{0,0,1}}}; }

Mat3 matRotX(float graus) { 
    float r = graus * PI / 180.0f, c = std::cos(r), s = std::sin(r);
    return {{{1,0,0},{0,c,-s},{0,s,c}}};
}
Mat3 matRotY(float graus) { 
    float r = graus * PI / 180.0f, c = std::cos(r), s = std::sin(r);
    return {{{c,0,s},{0,1,0},{-s,0,c}}};
}
Mat3 matRotZ(float graus) { 
    float r = graus * PI / 180.0f, c = std::cos(r), s = std::sin(r);
    return {{{c,-s,0},{s,c,0},{0,0,1}}};
}
Mat3 matRotEixo(int eixo, float graus) { 
    if (eixo == 0) return matRotX(graus);
    if (eixo == 1) return matRotY(graus);
    return matRotZ(graus);
}

float arred(float v) { 
    float r = std::round(v);
    return (std::fabs(v - r) < 0.001f) ? r : v;
}
Vec3 limparVec3(const Vec3& v) { return { arred(v.x), arred(v.y), arred(v.z) }; } 
Mat3 limparMat3(const Mat3& m) { 
    Mat3 r = m;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) r.m[i][j] = arred(r.m[i][j]);
    return r;
}

//Estado do Cubo
struct Cubinho { Vec3 pos; Mat3 orient; }; 
std::vector<Cubinho> cubinhos;

void inicializarCubo() {
    cubinhos.clear();
    for (float cx : {-1.0f, 1.0f})
        for (float cy : {-1.0f, 1.0f})
            for (float cz : {-1.0f, 1.0f})
                cubinhos.push_back({ {cx, cy, cz}, matIdentidade() });
}

//Lógica de Animação de Giro
bool girando = false;
int eixoGiro = 0;
float valorCamada = 1;
float sinalGiro = 1;
float anguloAtual = 0; 
std::vector<int> indicesGirando; 
const float VELOCIDADE_GIRO = 320.0f; 

void iniciarGiro(int eixo, float camada, float sinal) { 
    if (girando) return; // Impede girar duas coisas ao mesmo tempo
    eixoGiro = eixo; valorCamada = camada; sinalGiro = sinal; anguloAtual = 0; girando = true;
    indicesGirando.clear();
    for (int i = 0; i < (int)cubinhos.size(); i++) {
        float valor = (eixo==0) ? cubinhos[i].pos.x : (eixo==1) ? cubinhos[i].pos.y : cubinhos[i].pos.z;
        if (arred(valor) == camada) indicesGirando.push_back(i);
    }
}

void atualizarGiro(float dt) { 
    if (!girando) return;
    anguloAtual += VELOCIDADE_GIRO * dt;
    if (anguloAtual >= 90.0f) {
        Mat3 rot = matRotEixo(eixoGiro, sinalGiro * 90.0f);
        for (int i : indicesGirando) {
            cubinhos[i].pos = limparVec3(mulMatVec(rot, cubinhos[i].pos));
            cubinhos[i].orient = limparMat3(mulMatMat(rot, cubinhos[i].orient));
        }
        girando = false; anguloAtual = 0;
    }
}

//Controles de Câmera e Teclado
float camPitch = 20.0f, camYaw = -30.0f, zoom = -4.0f; 
bool arrastando = false;
double ultimoX = 0, ultimoY = 0;

void mouseButtonCallback(GLFWwindow* janela, int botao, int acao, int mods) {
    if (botao == GLFW_MOUSE_BUTTON_LEFT) {
        arrastando = (acao == GLFW_PRESS);
        if (arrastando) glfwGetCursorPos(janela, &ultimoX, &ultimoY);
    }
}

void cursorPosCallback(GLFWwindow* janela, double x, double y) {
    if (arrastando) {
        camYaw += (float)(x - ultimoX) * 0.4f;
        camPitch += (float)(y - ultimoY) * 0.4f;
        ultimoX = x; ultimoY = y;
    }
}

void keyCallback(GLFWwindow* janela, int tecla, int scancode, int acao, int mods) {
    if (acao != GLFW_PRESS) return;
    bool inv = (mods & GLFW_MOD_SHIFT) != 0; // Segure SHIFT para girar ao contrário
    
    switch (tecla) {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(janela, true); break; 
        //controles personalizados:
        case GLFW_KEY_R: iniciarGiro(0,  1.0f, inv ?  1 : -1); break; // Direita (Eixo X positivo)
        case GLFW_KEY_E: iniciarGiro(0, -1.0f, inv ? -1 :  1); break; // Esquerda (Eixo X negativo)
        case GLFW_KEY_F: iniciarGiro(1,  1.0f, inv ?  1 : -1); break; // Cima (Eixo Y positivo)
        case GLFW_KEY_D: iniciarGiro(1, -1.0f, inv ? -1 :  1); break; // Baixo (Eixo Y negativo)
    }
}

//Desenho OpenGL Fixo
void drawSubCube() {
    float s = 0.48f; 
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-s,-s, s); glVertex3f( s,-s, s); glVertex3f( s, s, s); glVertex3f(-s, s, s);
    glColor3f(1.0f, 0.5f, 0.0f); glVertex3f(-s,-s,-s); glVertex3f(-s, s,-s); glVertex3f( s, s,-s); glVertex3f( s,-s,-s);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(-s, s,-s); glVertex3f(-s, s, s); glVertex3f( s, s, s); glVertex3f( s, s,-s);
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-s,-s,-s); glVertex3f( s,-s,-s); glVertex3f( s,-s, s); glVertex3f(-s,-s, s);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-s,-s,-s); glVertex3f(-s,-s, s); glVertex3f(-s, s, s); glVertex3f(-s, s,-s);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( s,-s,-s); glVertex3f( s, s,-s); glVertex3f( s, s, s); glVertex3f( s,-s, s);
    glEnd();
}

void abrir_jogo_manual() {
    inicializarCubo();

    if (!glfwInit()) 
    {
        return;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo Animado - R, E, F, D", NULL, NULL);
    
    if (!window)
    { 
        glfwTerminate(); 
        return; 
    }

    glfwMakeContextCurrent(window);
    
    // Registra os eventos de teclado e mouse
    glfwSetMouseButtonCallback(window, mouseButtonCallback); 
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 800.0f / 600.0f;
    glFrustum(-aspect * 0.5f, aspect * 0.5f, -0.5f, 0.5f, 1.0f, 50.0f);
    glMatrixMode(GL_MODELVIEW);

    double tempoAnterior = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double agora = glfwGetTime();
        float dt = (float)(agora - tempoAnterior);
        tempoAnterior = agora;
        
        atualizarGiro(dt); // Atualiza os ângulos da animação se algo estiver girando

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Controla a câmera
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(camPitch, 1.0f, 0.0f, 0.0f);
        glRotatef(camYaw, 0.0f, 1.0f, 0.0f);

        // Desenha os 8 subcubos com suas rotações
        for (int i = 0; i < (int)cubinhos.size(); i++) {
            glPushMatrix();
            Vec3 pos = cubinhos[i].pos;
            Mat3 orient = cubinhos[i].orient; 

            // Se este subcubo faz parte do giro atual, aplica a rotação temporária de animação
            bool participa = girando && std::find(indicesGirando.begin(), indicesGirando.end(), i) != indicesGirando.end(); //[cite: 1]
            if (participa) {
                Mat3 parcial = matRotEixo(eixoGiro, sinalGiro * anguloAtual); 
                pos = mulMatVec(parcial, pos); 
                orient = mulMatMat(parcial, orient); 
            }

            // Traduz para a posição do subcubo (multiplicado por 0.5 pois eles oscilam entre -1 e 1)
            glTranslatef(pos.x * 0.5f, pos.y * 0.5f, pos.z * 0.5f);

            // Converte a matriz de orientação Mat3 para um formato 4x4 que o OpenGL entende (Coluna-Maior)
            float matrizGL[16] = {
                orient.m[0][0], orient.m[1][0], orient.m[2][0], 0,
                orient.m[0][1], orient.m[1][1], orient.m[2][1], 0,
                orient.m[0][2], orient.m[1][2], orient.m[2][2], 0,
                0,              0,              0,              1
            };
            glMultMatrixf(matrizGL); // Aplica a rotação do estado

            drawSubCube();
            glPopMatrix();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}