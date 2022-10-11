  # Obtener tu IP pública de Internet
  Programa simple hecho en C++ que te muestra tu ip pública a través de la consola. 
  Utiliza la API de windows para hacer la petición a un servidor de terceros y así obtener la IP. Solo sirve para sistemas operativos de Windows.
  
  ## Como compilar usando MinGW
  Lo relevante aquí es el parametro -lwinhttp, que es una librería de la API de windows que el programa necesita para hacer peticiones HTTP.
  ```g++ main.cpp -o main -lwinhttp```
  
