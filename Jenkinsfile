pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile.dev'
    }
    
  }
  stages {
    stage('Test') {
      steps {
        sh 'echo "test"'
      }
    }
  }
}