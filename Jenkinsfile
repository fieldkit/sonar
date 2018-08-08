@Library('conservify') _

timestamps {
    node () {
        conservifyBuild(name: 'sonar', repository: 'https://github.com/fieldkit/sonar.git')

        build job: "distribution", parameters: []
    }
}
