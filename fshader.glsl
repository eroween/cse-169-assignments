varying vec3 frag_normal;
varying vec3 vertPos;

uniform int mode;

struct Light {
    vec3    position;
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
};

uniform Light   lights[2];

void main() {
  vec3 normal = normalize(frag_normal);
  vec4 color = vec4(0, 0, 0, 1);

  for (int i = 0 ; i < 2 ; ++i) {
      vec3 lightDir = normalize(lights[i].position - vertPos);
      float lambertian = max(dot(lightDir, normal), 0.0);
      float specular = 0.0;
      if(lambertian > 0.0) {
          vec3 viewDir = normalize(-vertPos);
          // blinn phong
          vec3 halfDir = normalize(lightDir + viewDir);
          float specAngle = max(dot(halfDir, normal), 0.0);
          specular = pow(specAngle, 16.0);
      }
      color += vec4(lights[i].ambient + lambertian * lights[i].diffuse + specular * lights[i].specular, 0.0);
  }

  gl_FragColor = color;
}
