pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile.dev'
    }
    
  }
  stages {
    stage('Test') {
      steps {
        sh 'build/kui_test'
      }
    }
  }
}