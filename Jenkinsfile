pipeline {
  agent {
    label "local"
  }

  options {
    skipDefaultCheckout(true)
    timeout(time: 20, unit: 'MINUTES')
    buildDiscarder(logRotator(numToKeepStr: '10', artifactNumToKeepStr: '10'))
    timestamps()
  }

  stages {
    stage("Preparation") {
      steps {
        script {
          def scmEnv = checkout(scm)
          currentBuild.displayName = "${env.BUILD_NUMBER} ${scmEnv.GIT_COMMIT.take(8)}"
        }
      }
    }

    stage("Build") {
      steps {
        echo "#INFO: Building project"
        dir("build") {
          sh "cmake .. && make -s"
        }
      }
    }

    stage("Unit tests") {
      steps {
        echo "#INFO: Running unit tests"
        dir("build") {
          sh "ctest -V --no-compress-output -T test"
        }
      }

      post {
        always {
          xunit(
            tools: [CTest(
              pattern: "build/Testing/*/Test.xml",
              failIfNotNew: true,
              stopProcessingIfError: true
            )],
            thresholds: [failed(unstableThreshold: '0', failureThreshold: '0')]
          )
        }
      }
    }
  }

  post {
    always {
      chuckNorris()
    }

    cleanup {
      cleanWs()
    }
  }
}
