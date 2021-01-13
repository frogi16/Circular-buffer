pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile'
    }

  }
  stages {
    stage('Test') {
      steps {
        sh '''cd build;
cmake ../;
make;
./runTests;'''
      }
    }

  }
}