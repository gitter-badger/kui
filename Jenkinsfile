pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile.dev'
    }
    
  }
  stages {
    stage('Test') {
      steps {
        sh './kui_test'
      }
    }
  }
}