pipeline {
  agent dockerfile Dockerfile
  stages {
    stage('Build') {
      steps {
        sh '''mkdir build
cd build

cmake ..
make'''
      }
    }
  }
}
