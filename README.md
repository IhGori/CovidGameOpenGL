# Covid Game Project OpenGL with C++
Projeto desenvolvido durante disciplina de Computação Gráfica

Utilizando-se da linguagem de programação C++ com API OpenGL para desenvolvimento de aplicações gráficas.

Jogo que utiliza como base o Dinosaur Game do Google, em que equipe utilizou-se da temática do período em que o mundo vivia do Covid, substituindo itens
como o dinossauro por um personagem que ao desviar de objetos (Vírus do Covid) ganha pontuação ao decorrer do tempo e com choques com a Vacina ele ganha 
status de imunidade. É possível personalização do ambiente.

- Projeto desenvolvido em parceria com amigos do curso:
    - Paulo Lucas: https://github.com/plucasbm
    - Marcos Filipe

Guia abaixo referente a instalação para o Dev C++

## Requerimentos
<ul>
  <li>Baixar o Dev C++, caso deseje utilizar outro compilador, realizar busca de como executar instalações dos pacotes do OpenGL para o respectivo compilador;</li>
  <li>Baixar e instalar pacote do OpenGL Utility Tollkit (GLUT).</li>
</ul>

## Instalação
Guia indicado pelo professor da disciplina Computação Gráfica: Jorge Cavalcanti da Universidade Federal do Vale do São Francisco (UNIVASF) (http://www.univasf.edu.br/~jorge.cavalcanti/configdev.html)
<ul>
  <li>Descompacte o arquivo libglut.a e libglut32.a no diretório /lib do Dev-C++;</li>
  <li>Descompacte o arquivo glut32.dll no diretório windows/system</li>
  <li>No Dev C++, vá em Ferramentas, opções do Compilador e digite os comandos -lopengl32, -lglu32 , -lglut32, -lwinmm, -lgdi32, conforme figura abaixo:</li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/imagem_config.png">
  <li>Crie um projeto novo no Dev, escolhendo Console Aplicattion, Linguagem C. Especifique um caminho válido que você possa gravar os arquivos</li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/image002.jpg">
  <li> Com o projeto criado, vá no menu Projeto > Opções do Projeto e na Guia Parâmetros, acrescente os comandos:
     <ul>
       <li>-lopengl32</li>
       <li>-lglu32</li>
       <li>-lglut32</li>
       <li>-lwinmm</li>
       <li>-lgdi32</li>
     </ul>
  </li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/image004.jpg">
</ul>

Relembrando, todo tutorial de instalação supracitado foi retirado do guia de instalação do professor Jorge Cavalcanti (http://www.univasf.edu.br/~jorge.cavalcanti/configdev.html).

<br>
<br>
<br>

## Jogo
<blockquote class="imgur-embed-pub" lang="en" data-id="WsW9utZ"><a href="https://imgur.com/WsW9utZ">View post on imgur.com</a></blockquote><script async src="//s.imgur.com/min/embed.js" charset="utf-8"></script>
<img src="https://imgur.com/WsW9utZ">
<img src="https://imgur.com/TTVrane">
<img src="https://imgur.com/HO9hwFc">

Project developed during the course of Computer Graphics

Using the C++ programming language with OpenGL API to develop graphical applications.

Game that uses Google's Dinosaur Game as a basis, in which the team used the theme of the period in which the world lived from Covid, replacing items
like the dinosaur by a character who by dodging objects (Covid Virus) gains points over time and with shocks with the Vaccine he gains
immunity status. Customization of the environment is possible.

- Project developed in partnership with friends from the course:
    - Paulo Lucas: https://github.com/plucasbm
    - Marco Filipe

Guide below regarding installation for Dev C++

## Requirements
<ul>
  <li>Download Dev C++, if you want to use another compiler, search for how to install OpenGL packages for the respective compiler;</li>
  <li>Download and install OpenGL Utility Tollkit (GLUT) package.</li>
</ul>

## Installation
Guide recommended by the professor of Computer Graphics: Jorge Cavalcanti from the Federal University of Vale do São Francisco (UNIVASF) (http://www.univasf.edu.br/~jorge.cavalcanti/configdev.html)
<ul>
  <li>Unzip the libglut.a and libglut32.a files in the Dev-C++ /lib directory;</li>
  <li>Unzip the glut32.dll file in the windows/system directory</li>
  <li>In Dev C++, go to Tools, Compiler options and type the commands -lopengl32, -lglu32 , -lglut32, -lwinmm, -lgdi32, as shown below:</li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/imagem_config.png">
  <li>Create a new project in Dev, choosing Console Aplicattion, Language C. Specify a valid path where you can save the files</li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/image002.jpg">
  <li> With the project created, go to the menu Project > Project Options and in the Parameters Tab, add the commands:
     <ul>
       <li>-lopengl32</li>
       <li>-lglu32</li>
       <li>-lglut32</li>
       <li>-lwinmm</li>
       <li>-lgdi32</li>
     </ul>
  </li>
  <img src="http://www.univasf.edu.br/~jorge.cavalcanti/configdev_arquivos/image004.jpg">
</ul>

As a reminder, the installation tutorial mentioned above was taken from Professor Jorge Cavalcanti's installation guide (http://www.univasf.edu.br/~jorge.cavalcanti/configdev.html).
