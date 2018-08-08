@Library('conservify') _

properties([
    [$class: 'BuildDiscarderProperty', strategy: [$class: 'LogRotator', numToKeepStr: '5']],
    pipelineTriggers([[$class: 'GitHubPushTrigger']]),
])

timestamps {
    node () {
        conservifyBuild(name: 'sonar', repository: 'https://github.com/fieldkit/sonar.git')

        build job: "distribution", parameters: []
    }
}
