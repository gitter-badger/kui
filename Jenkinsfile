pipeline {
  agent any
  stages {
    stage('Build Image') {
      steps {
        sh '''# Ensure image is deleted
docker rmi -f kui_jenkins || :


docker build -t kui_jenkins -f Dockerfile.dev .'''
      }
    }
    stage('Test') {
      steps {
        sh 'docker run --rm kui_jenkins build/kui_test'
      }
    }
  }
}