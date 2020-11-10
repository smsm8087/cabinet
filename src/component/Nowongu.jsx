import React, { Component } from 'react'
import { Link } from "react-router-dom";

class Nowongu extends Component {

  render() {
    return (
      <React.Fragment>
        <h4 className="title">노원구</h4>
        <input type="radio" name="nowongu" id="sanggye" defaultChecked={true}/>
        <input type="radio" name="nowongu" id="junggye" />
        <input type="radio" name="nowongu" id="woulgye" />
        <div className="service-box">
          <div className="service-list-box border-b">
            <ul>
              <li className="margin-b-20 service-list-title">거래건수 top3 동</li>
              <li>
                <label htmlFor="sanggye">상계동</label>
              </li>
              <li>
                <label htmlFor="junggye">중계동</label>
              </li>
              <li>
                <label htmlFor="woulgye">월계동</label>
              </li>
            </ul>

            <div className="service-list service-sanggye">
              <ul>
                <li>
                  <Link to="/"><span>1. 포레나노원</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>2. 상계주공7단지</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>3. 노원롯데캐슬시그니쳐</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>4. 상계주공9단지</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>5. 보람</span></Link><span className="color-red">2▲</span>
                </li>
                <li>
                  <Link to="/sang"><span>6. 상계주공16단지</span></Link><span className="color-red">2▲</span>
                </li>
                <li>
                  <Link to="/"><span>7. 상계주공6단지</span></Link><span className="color-red">2▼</span>
                </li>
                <li>
                  <Link to="/"><span>8. 벽산</span></Link><span className="color-red">2▲</span>
                </li>
                <li>
                  <Link to="/"><span>9. 상계주공3단지</span></Link><span className="color-red">2▼</span>
                </li>
                <li>
                  <Link to="/"><span>10. 상계주공1단지</span></Link><span className="color-red">신규</span>
                </li>
              </ul>
            </div>

            <div className="service-list service-junggye">
              <ul>
                <li>
                  <Link to="/"><span>1. 중계그린</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>2. 중계무지개</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>3. 중계주공5단지</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>4. 중계롯데상아</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>5. 건영2차</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>6. 중계주공2단지</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>7. 청구3차</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>8. 염광</span></Link><span className="color-red">-</span>
                </li>
                <li>
                  <Link to="/"><span>9. 중계주공4단지</span></Link><span className="color-red">1▲</span>
                </li>
                <li>
                  <Link to="/"><span>10. 중계2차한화꿈에그린더퍼스트</span></Link><span className="color-red">신규</span>
                </li>
              </ul>
            </div>

            <div className="service-list service-woulgye">
              <ul>
                <li>
                  <Link to="/"><span>1. 첨단대우</span></Link><span className="color-red">2▲</span>
                </li>
                <li>
                  <Link to="/"><span>2. 첨단동부</span></Link><span className="color-red">1▼</span>
                </li>
                <li>
                  <Link to="/"><span>3. 첨단남양파크</span></Link><span className="color-red">2▲</span>
                </li>
                <li>
                  <Link to="/"><span>4. 첨단산업기지라인1차</span></Link><span className="color-red">2▼</span>
                </li>
                <li>
                  <Link to="/"><span>5. 첨단삼성</span></Link><span className="color-red">신규</span>
                </li>
                <li>
                  <Link to="/"><span>6. 기산</span></Link><span className="color-red">신규</span>
                </li>
                <li>
                  <Link to="/"><span>7. 첨단선경</span></Link><span className="color-red">1▼</span>
                </li>
                <li>
                  <Link to="/"><span>8. 첨단과학산업기지라인3차</span></Link><span className="color-red">신규</span>
                </li>
                <li>
                  <Link to="/"><span>9. 월계모아</span></Link><span className="color-red">신규</span>
                </li>
                <li>
                  <Link to="/"><span>10. 첨단산업기지라인2차</span></Link><span className="color-red">신규</span>
                </li>
              </ul>
            </div>
          </div>
        </div>


        <input type="radio" name="nowongu1" id="sanggye1" defaultChecked={true}/>
        <input type="radio" name="nowongu1" id="junggye1" />
        <input type="radio" name="nowongu1" id="woulgye1" />
        <div className="service-box">
          <div className="service-list-box">
            <ul>
              <li className="margin-b-20 service-list-title">신고가건수 top3 동</li>
              <li>
                <label htmlFor="sanggye1">상계동</label>
              </li>
              <li>
                <label htmlFor="junggye1">중계동</label>
              </li>
              <li>
                <label htmlFor="woulgye1">공릉동</label>
              </li>
            </ul>

            <div className="service-list service-sanggye1">
              <ul className="news-list">
                <li className="news-title">NEWS</li>
                <li>
                  <span>상계2택지개발지구 공영주차장 부지에 어울림체육센터 들어선다 2020.07.09</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=277&arti_id=0004714830" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>홍릉서 10㎞ 상계동에…또 바이오클러스터? 2020.02.05</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=009&arti_id=0004512441" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>노원구, 상계동에 437억 투입해 행정복합타운 건립 2019.11.14</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=421&arti_id=0004304009" target="_blank">뉴스 확인</a>
                </li>
              </ul>
            </div>

            <div className="service-list service-junggye1">
              <ul className="news-list">
                <li className="news-title">NEWS</li>
                <li>
                  <span>중계동 노인복지주택 자리, 아파트용지로 바뀐다 2020.05.22</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=277&arti_id=0004683307" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>중계동·장위뉴타운 '동북선' 혜택 본다 2020.02.16</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=015&arti_id=0004291001" target="_blank">뉴스 확인</a>
                </li>
              </ul>
            </div>

            <div className="service-list service-woulgye1">
              <ul className="news-list">
                <li className="news-title">NEWS</li>
                <li>
                  <span>공릉역 초역세권에 아파트 450가구 들어선다 2020.10.08</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=008&arti_id=0004481405" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>공릉동 구 화랑대역 일대 '문화공원'으로 조성 2020.06.04</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=008&arti_id=0004419644" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>노원구 공릉1구역에 생활체육시설 짓는다 2020.04.30</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=277&arti_id=0004670797" target="_blank">뉴스 확인</a>
                </li>
                <li>
                  <span>[동네방네]노원구, ‘돗가비 마을’ 도시 재생 2020.02.10</span>
                  <a href="https://land.naver.com/news/newsRead.nhn?type=region&prsco_id=018&arti_id=0004572095" target="_blank">뉴스 확인</a>
                </li>
              </ul>
            </div>
          </div>
        </div>
      </React.Fragment>
    )
  }

}

export default Nowongu