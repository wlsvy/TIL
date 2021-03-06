# AWS

### Amazon EC2

- [AWS 문서](https://docs.aws.amazon.com/ko_kr/AWSEC2/latest/UserGuide/concepts.html)

Amazon Elastic Compute Cloud(Amazon EC2)는 Amazon Web Services(AWS) 클라우드에서 확장 가능 컴퓨팅 용량을 제공합니다. Amazon EC2를 사용하면 하드웨어에 선투자할 필요가 없어 더 빠르게 애플리케이션을 개발하고 배포할 수 있습니다. Amazon EC2를 통해 원하는 만큼 가상 서버를 구축하고 보안 및 네트워크 구성과 스토리지 관리가 가능합니다.

### Amazon 머신 이미지(AMI)

- [AWS 문서](https://docs.aws.amazon.com/ko_kr/AWSEC2/latest/UserGuide/AMIs.html)

**Amazon 머신 이미지(AMI)**는 인스턴스를 시작하는 데 필요한 정보를 제공합니다. 인스턴스를 시작할 때 AMI를 지정해야 합니다. 동일한 구성의 인스턴스가 여러 개 필요할 때는 한 AMI에서 여러 인스턴스를 시작할 수 있습니다. 서로 다른 구성의 인스턴스가 필요할 때는 다양한 AMI를 사용하여 인스턴스를 시작하면 됩니다.

AMI는 다음을 포함합니다.

- 1개 이상의 Amazon Elastic Block Store(Amazon EBS) 스냅샷 또는, 인스턴스 스토어 기반 AMI의 경우, 인스턴스의 루트 볼륨에 대한 템플릿(예: 운영 체제, 애플리케이션 서버, 애플리케이션)
- AMI를 사용하여 인스턴스를 시작할 수 있는 AWS 계정을 제어하는 시작 권한
- 시작될 때 인스턴스에 연결할 볼륨을 지정하는 블록 디바이스 매핑

### Amazon EBS 볼륨

- [AWS 문서](https://docs.aws.amazon.com/ko_kr/AWSEC2/latest/UserGuide/ebs-volumes.html)

Amazon EBS 볼륨은 내구성이 있는 블록 수준 스토리지 디바이스이며 인스턴스를 연결하는 것이 가능합니다. 볼륨을 인스턴스에 연결하면 물리적 하드 드라이브처럼 사용할 수 있습니다. EBS 볼륨은 유연합니다. 현재 세대 인스턴스 유형에 연결된 현재 세대 볼륨의 경우 크기를 동적으로 늘리고 프로비저닝된 IOPS 용량을 수정하며 라이브 프로덕션 볼륨의 볼륨 유형을 변경할 수 있습니다.

인스턴스의 시스템 드라이브 또는 데이터베이스 애플리케이션용 스토리지 등 자주 업데이트해야 하는 데이터의 경우 EBS 볼륨을 기본 스토리지로 사용할 수 있습니다.

EBS 볼륨 사용의 이점

- 데이터 가용성 : EBS 볼륨을 생성하면 단일 하드웨어 구성 요소의 장애로 인한 데이터 손실을 방지하기 위해 해당 가용 영역 내에서 자동으로 복제됩니다.
- 데이터 지속성 : EBS 볼륨은 인스턴스의 수명에 관계없이 유지되는 오프 인스턴스 스토리지입니다. 사용자는 데이터가 유지되는 동안 볼륨 사용량에 대한 비용을 계속해서 지불합니다.
- 데이터 암호화
- 스냅샷 : Amazon EBS를 사용하면 모든 EBS 볼륨의 스냅샷(백업)을 생성하고 볼륨 내 데이터 사본을 다중 가용 영역에 중복 저장이 가능한 Amazon S3에 작성할 수 있습니다. 볼륨이 실행 중인 인스턴스에 연결되어 있지 않아도 스냅샷을 만드는 데는 문제가 없습니다.
- 유연성
