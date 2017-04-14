pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile'
    }
    
  }
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