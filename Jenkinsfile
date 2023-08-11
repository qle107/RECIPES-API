node {
  stage('SCM') {
    checkout scm
  }
    stage('SonarQube Analysis') {
      def scannerHome = tool 'C:\Users\lequa\Downloads\sonar-scanner-cli-5.0.1.3006-windows\sonar-scanner-5.0.1.3006-windows\bin';
      withSonarQubeEnv(){
    sh "${scannerHome}/bin/sonar-scanner"
    }
  }
}
